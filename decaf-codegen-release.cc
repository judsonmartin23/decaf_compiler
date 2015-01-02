#include "decafs.h"
#include "fstream"

extern int yyparse(void);
extern ParseTree * top;
extern Symtab * currentScope;
extern FILE * yyin;

ofstream * currentFile;
string className;
string sourceName;
int currentLabel;
vector<string> breakLabels;

void generate_statement(ParseTree * statement);
void generate_block(ParseTree * block);
void generate(ParseTree * tree);


string generate_label() {
  string chars [16] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
  string label = "LABEL0x";
  string temp = label + chars[currentLabel/16];
  label = temp;
  temp = label + chars[currentLabel%16];
  label = temp;
  currentLabel++;
  return label;
}

string decaf_type_to_jasmin_type(string tname)
{
  string array = "";
  while (tname[tname.size()-1]==']') {
    array += "[";
    tname = tname.substr(0, tname.size()-3);
  }
  if (tname=="string")
    tname = "Ljava/lang/String;";
  else if (tname=="int") 
    tname = "I";
  else if (tname=="bool")
    tname = "Z";
  else if (tname=="double")
    tname = "D";
  else if (tname=="void")
    tname = "V";
  else
    tname = "L_" + tname + ";";
  return array + tname;
}

string jasmin_type_from_tree(ParseTree * typetree)
{
  if (typetree->token->type == T_Void)
    return "V";  // void if the tree is NULL
  return decaf_type_to_jasmin_type(typetree->token->text);
}

string decaf_type(ParseTree * exprTree)
{
  return exprTree->stype;
}

string jasmin_binop_instruction(string op, string type)
{
  if (type=="int") {
    if (op=="+")
      return "iadd";
    if (op=="-")
      return "isub";
    if (op=="*")
      return "imul";
    if (op=="/")
      return "idiv";
    if (op=="%")
      return "irem";
    cout << "unimplemented binary operator " << op << " for type int" << endl;
    exit(1);
  }
  if (type=="double") {
    if (op=="+")
      return "dadd";
    if (op=="-")
      return "dsub";
    if (op=="*")
      return "dmul";
    if (op=="/")
      return "ddiv";
    if (op=="%")
      return "drem";
    cout << "unimplemented binary operator " << op << " for type double" << endl;
    exit(1);
  }
  if (type=="bool") {
    if (op=="&&")
      return "iand";
    if (op=="||")
      return "ior";
    cout << "unimplemented binary operator " << op << " for type bool" << endl;
    exit(1);
  }
  cout << "unimplemented type " << type << " in jasmin_binop_instruction." << endl;
  exit(1);
}

string jasmin_boolean_instruction(string op, string type)
{
  if ((type=="bool") or (type=="int")) {
    if (op=="==")
      return "if_icmpne             ";
    if (op=="!=")
      return "if_icmpeq             ";
    if (op==">=")
      return "if_icmplt             ";
    if (op=="<=")
      return "if_icmpgt             ";
    if (op==">")
      return "if_icmple             ";
    if (op=="<")
      return "if_icmpge             ";
    cout << "unimplemented binary operator " << op << " for type " << type << endl;
    exit(1);
  }
  else if (type=="double") {
    if (op=="==")
      return "ifne                  ";
    if (op=="!=")
      return "ifeq                  ";
    if (op==">=")
      return "iflt                  ";
    if (op=="<=")
      return "ifgt                  ";
    if (op==">")
      return "ifle                  ";
    if (op=="<")
      return "ifge                  ";
    cout << "unimplemented binary operator " << op << " for type double" << endl;
    exit(1);
  }
  else {
    if (op=="==")
      return "if_acmpne             ";
    if (op=="!=")
      return "if_acmpeq             ";
    cout << "unimplemented binary operator " << op << " for type " << type << endl;
    exit(1);
  }
  cout << "unimplemented type " << type << " in jasmin_boolean_instruction." << endl;
  exit(1);
}

string jasmin_compare_double_instruction(string op)
{
  if (op=="==" or op=="!=" or op==">=" or op==">")
    return "dcmpl";
  else
    return "dcmpg";
}

string jasmin_minus_instruction(string type)
{
  if (type=="int")
    return "ineg";
  if (type=="double")
    return "dneg";
  cout << "unimplemented type " << type << " in jasmin_minus_instruction." << endl;
  exit(1);
}

string return_mnemonic(string typestr)
{
  if (typestr=="string")
    return "areturn";
  else if (typestr=="int")
    return "ireturn";
  else if (typestr=="bool")
    return "ireturn";
  else if (typestr=="double")
    return "dreturn";
  return "areturn";
}

string load_mnemonic(string typestr)
{
  if (typestr=="string")
    return "aload                ";
  else if (typestr=="int")
    return "iload                ";
  else if (typestr=="bool")
    return "iload                ";
  else if (typestr=="double")
    return "dload                ";
  return "aload                ";
}

string store_mnemonic(string typestr)
{
  if (typestr=="string")
    return "astore               ";
  else if (typestr=="int")
    return "istore               ";
  else if (typestr=="bool")
    return "istore               ";
  else if (typestr=="double")
    return "dstore               ";
  return "astore               ";
}

void generate_variable_load(string varname) {
  S_variable * var;
  if ((currentClass!=NULL) and (currentScope->lookup(varname)==NULL)) {
    bool found = false;
    S_class* temp = currentClass->parentClass;
    while ((temp != NULL) and !(found)) {
      for (size_t i=0; i<temp->fields.size(); i++) {
	if (temp->fields[i]->kind() == "S_variable") {
	  if (((S_variable*)(temp->fields[i]))->name == varname) {
	    var = (S_variable*)(temp->fields[i]);
	    found = true;
	  }
	}
      }
      temp = temp->parentClass;
    }
  }
  else
    var=(S_variable *)currentScope->lookup(varname);
  cout << "Identifier '" << varname << "' is type " << var->type->name << endl;
  if ((var->global==false) and (var->instance==false))
    *currentFile << "   " << load_mnemonic(var->type->name) 
		 << " " << var->number <<endl;
  else if (var->global==true)
    *currentFile << "   getstatic             " << className << "/" 
		 << var->name << " " 
		 << decaf_type_to_jasmin_type(var->type->name) << endl;
  else if (var->instance==true)
    *currentFile << "   aload                 0" << endl << "   getfield              " << className << "/" 
		 << var->name << " " 
		 << decaf_type_to_jasmin_type(var->type->name) << endl;
}

void generate_expr(ParseTree * expr)
{
  cout << "Generating expression..." << endl;
  if (expr->description=="constant" and expr->children[0]->
      token->type==T_IntConstant) {
    *currentFile << "   ldc                   " << expr->children[0]->token->text << endl;
  }
  else if (expr->description=="constant" and expr->children[0]->
      token->type==T_StringConstant) {
    *currentFile << "   ldc                   " << expr->children[0]->token->text << endl;
  }
  else if (expr->description=="constant" and expr->children[0]->
      token->type==T_DoubleConstant) {
    *currentFile << "   ldc2_w                " << expr->children[0]->token->text << endl;
  }
  else if (expr->description=="constant" and expr->children[0]->
	   token->type==T_BoolConstant) {
    if (expr->children[0]->token->text == "true")
      *currentFile << "   iconst_1" << endl;
    else
      *currentFile << "   iconst_0" << endl;
  }
  else if (expr->description=="constant" and expr->children[0]->
	   token->type==T_Null) {
    *currentFile << "   aconst_null" << endl;
  }
  else if (expr->description=="readline")
    *currentFile << "   invokestatic          " << sourceName << "/readLineFunc()Ljava/lang/String;" << endl;
  else if (expr->description=="readinteger")
    *currentFile << "   invokestatic          " << sourceName << "/readIntFunc()I" << endl;
  else if (expr->description=="binexpr") {
    generate_expr(expr->children[0]);
    generate_expr(expr->children[2]);
    if ((expr->stype!="bool") or (expr->children[1]->token->text=="&&") or (expr->children[1]->token->text=="||")) {
      *currentFile << "   " 
		   << jasmin_binop_instruction(expr->children[1]->token->text,
					       decaf_type(expr)) << endl;
    }
    else {
      string labelOne = generate_label();
      string labelTwo = generate_label();
      if (decaf_type(expr->children[0])=="double")
	*currentFile << "   " << jasmin_compare_double_instruction(expr->children[1]->token->text) << endl;
      *currentFile << "   "
		   << jasmin_boolean_instruction(expr->children[1]->token->text,
						 decaf_type(expr->children[0]))
		   << labelOne << endl << "   iconst_1" << endl
		   << "   goto                  " << labelTwo << endl
		   << labelOne << ":" << endl << "   iconst_0" << endl
		   << labelTwo << ":" << endl;
    }
  }
  else if (expr->description=="unexpr") {
    generate_expr(expr->children[1]);
    if (expr->children[0]->token->text=="-")
      *currentFile << "   " << jasmin_minus_instruction(decaf_type(expr->children[1])) << endl;
    else {
      *currentFile << "   const_1" << endl << "   ixor" << endl;
    }
  }
  else if (expr->description=="identifier") {
    generate_variable_load(expr->children[0]->token->text);
  }
  else if (expr->description=="new") {
    *currentFile << "   new                   _" << expr->children[1]->token->text 
		 << endl << "   dup" << endl << "   invokespecial         _" 
		 << expr->children[1]->token->text << "/<init>()V" << endl;
  }
  else if (expr->description=="functioncall") {
    string jasmin_actuals = "";
    string temp;
    string decaf_type;
    if (currentClass!=NULL)
      *currentFile << "   aload                 0" << endl;
    for (size_t i=0; i<expr->children[1]->children[0]->children.size(); i++) {
      generate_expr(expr->children[1]->children[0]->children[i]);
      temp = jasmin_actuals + decaf_type_to_jasmin_type(expr->children[1]->children[0]->children[i]->stype);
      jasmin_actuals = temp;
    }
    if (currentClass==NULL)
      *currentFile << "   invokestatic          " << className << "/" 
		   << expr->children[0]->children[0]->token->text << "(" 
		   << jasmin_actuals << ")" << decaf_type_to_jasmin_type(expr->stype) << endl;
    else
      *currentFile << "   invokevirtual       " << className << "/" 
		   << expr->children[0]->children[0]->token->text << "(" 
		   << jasmin_actuals << ")" << decaf_type_to_jasmin_type(expr->stype) << endl;
  }
  else if (expr->description=="methodcall") {
    generate_expr(expr->children[0]);
    string jasmin_actuals = "";
    string temp;
    string decaf_type;
    int numFormals = 1;
    for (size_t i=0; i<expr->children[2]->children[0]->children.size(); i++) {
      generate_expr(expr->children[2]->children[0]->children[i]);
      temp = jasmin_actuals + decaf_type_to_jasmin_type(expr->children[2]->children[0]->children[i]->stype);
      jasmin_actuals = temp;
      numFormals++;
    }
    if (currentScope->lookup(expr->children[0]->stype)->kind()=="S_class"){
    *currentFile << "   invokevirtual         _" << expr->children[0]->stype << "/" 
		 << expr->children[1]->children[0]->token->text << "("
		 << jasmin_actuals << ")" << decaf_type_to_jasmin_type(expr->stype) << endl;
    }
    else if (currentScope->lookup(expr->children[0]->stype)->kind()=="S_interface"){
    *currentFile << "   invokeinterface       _" << expr->children[0]->stype << "/" 
		 << expr->children[1]->children[0]->token->text << "("
		 << jasmin_actuals << ")" << decaf_type_to_jasmin_type(expr->stype) << " " << numFormals << endl;
    }
  }
  else if (expr->description=="this") {
    *currentFile << "   aload                 0" << endl;
  }
  else if (expr->description=="varacc") {
    generate_expr(expr->children[0]);
    S_variable * var;
    S_class* thisClass = ((S_class *)(currentScope->lookup(expr->children[0]->stype)));
    bool found = false;
    while ((thisClass != NULL) and (! found)) {
      for (size_t i=0; i<thisClass->fields.size(); i++) {
	if (thisClass->fields[i]->kind() == "S_variable") {
	  if (expr->children[1]->token->text ==
	      ((S_variable*)(thisClass->fields[i]))->name) {
	    var = (S_variable*)(thisClass->fields[i]);
	    found = true;
	  }
	}
      }
      if (found==false)
	thisClass = thisClass->parentClass;
    }
    *currentFile << "   getfield              _" << thisClass->name << "/" 
		 << var->name << " " 
		 << decaf_type_to_jasmin_type(var->type->name) << endl;
  }
  else {
    cout << "UNIMPLEMENTED in generate_expr : " << expr->description << endl;
    exit(1);
  }
}

void generate_print_expr(ParseTree * expr)
{
  cout << "Generating print_expr..." << endl;
  *currentFile << "   getstatic             java/lang/System/out "
   "Ljava/io/PrintStream;" << endl;
  generate_expr(expr);
  *currentFile << "   invokevirtual         java/io/PrintStream/print("
               << decaf_type_to_jasmin_type(decaf_type(expr)) << ")V" << endl;
}

void generate_print(ParseTree * printstmt)
{
  cout << "Generating print..." << endl;
  ParseTree *exprs = printstmt->children[1];
  for (size_t i=0;i<exprs->children.size();i++) 
    generate_print_expr(exprs->children[i]);
  // followed by a println...
  *currentFile << "   getstatic             java/lang/System/out "
   "Ljava/io/PrintStream;" << endl;
  *currentFile << "   invokevirtual         java/io/PrintStream/println()V" << endl;
}

void generate_assign(ParseTree * assign)
{
  cout << "Generating assign..." << endl;
  S_variable * var;
  if (assign->children[0]->description=="identifier") {
    var = (S_variable *)currentScope->lookup(assign->children[0]->children[0]->token->text);
    if ((var->global==false) and (var->instance==false)) {
      generate_expr(assign->children[2]);
      *currentFile << "   " << store_mnemonic(var->type->name) 
		   << " " << var->number <<endl;
    }
    else if (var->global==true) {
      generate_expr(assign->children[2]);
      *currentFile << "   putstatic             " << className << "/" 
		   << var->name << " " 
		   << decaf_type_to_jasmin_type(var->type->name) << endl;
    }
    else if (var->instance==true) {
      *currentFile << "   aload                 0" << endl;
      generate_expr(assign->children[2]);
      *currentFile << "   putfield              " << className << "/" 
		   << var->name << " " 
		   << decaf_type_to_jasmin_type(var->type->name) << endl;
    }
  }
  else if (assign->children[0]->description=="varacc") {
    generate_expr(assign->children[0]->children[0]);
    S_class* thisClass = ((S_class *)(currentScope->lookup(assign->children[0]->children[0]->stype)));
    bool found = false;
    while ((thisClass != NULL) and (! found)) {
      for (size_t i=0; i<thisClass->fields.size(); i++) {
	if (thisClass->fields[i]->kind() == "S_variable") {
	  if (assign->children[0]->children[1]->token->text ==
	      ((S_variable*)(thisClass->fields[i]))->name) {
	    var = (S_variable*)(thisClass->fields[i]);
	    found = true;
	  }
	}
      }
      if (found==false)
	thisClass = thisClass->parentClass;
    }
    generate_expr(assign->children[2]);
    *currentFile << "   putfield              _" << thisClass->name << "/" 
		 << var->name << " " 
		 << decaf_type_to_jasmin_type(var->type->name) << endl;
  }
}

void generate_ifstmt(ParseTree * ifstmt)
{
  cout << "Generating ifstmt..." << endl;
  generate_expr(ifstmt->children[0]);
  string labelOne = generate_label();
  *currentFile << "   ifeq                  " << labelOne << endl;
  generate_statement(ifstmt->children[1]);
  if (ifstmt->children.size()==3) {
    string labelTwo = generate_label();
    *currentFile << "   goto                  " << labelTwo << endl << labelOne << ":" << endl;
    generate_statement(ifstmt->children[2]);
    *currentFile << labelTwo << ":" << endl;
  }
  else
    *currentFile << labelOne << ":" << endl;
}

void generate_whilestmt(ParseTree * whilestmt)
{
  cout << "Generating whilestmt..." << endl;
  string labelOne = generate_label();
  string labelTwo = generate_label();
  *currentFile << labelOne << ":" << endl;
  generate_expr(whilestmt->children[0]);
  *currentFile << "   ifeq                  " << labelTwo << endl;
  breakLabels.push_back(labelTwo);
  generate_statement(whilestmt->children[1]);
  breakLabels.pop_back();
  *currentFile << "   goto                  " << labelOne << endl << labelTwo << ":" << endl;
}

void generate_forstmt(ParseTree * forstmt)
{
  cout << "Generating forstmt..." << endl;
  if (forstmt->children[0]!=NULL)
    generate_statement(forstmt->children[0]);
  string labelOne = generate_label();
  string labelTwo = generate_label();
  *currentFile << labelOne << ":" << endl;
  generate_expr(forstmt->children[1]);
  *currentFile << "   ifeq                  " << labelTwo << endl;
  breakLabels.push_back(labelTwo);
  generate_statement(forstmt->children[3]);
  breakLabels.pop_back();
  if (forstmt->children[2]!=NULL)
    generate_statement(forstmt->children[2]);
  *currentFile << "   goto                  " << labelOne << endl << labelTwo << ":" << endl;
}

void generate_breakstmt()
{
  cout << "Generating breakstmt..." << endl;
  *currentFile << "   goto                  " << breakLabels.back() << endl;
}

void generate_preamble(string className, string superClassName, ParseTree * tree)
{
  *currentFile << ".class                   public " << className << endl
               << ".super                   " 
               <<  (superClassName==""?"java/lang/Object":superClassName)
               << endl
               << endl;
  bool globals=false;
  for (size_t i=0; i<tree->children[0]->children.size(); i++) {
    if (tree->children[0]->children[i]->children[0]->description=="variabledecl") {
      globals=true;
      *currentFile << ".field                   static " 
		   << tree->children[0]->children[i]->children[0]->children[0]->children[1]->token->text;
      *currentFile << " " << decaf_type_to_jasmin_type(tree->children[0]->children[i]->children[0]->
						       children[0]->children[0]->token->text) << endl;
    }
  }
  if (globals)
    *currentFile << endl << endl;

  *currentFile << ".method                  public <init>()V" << endl;
  *currentFile << "   .limit stack          1" << endl;
  *currentFile << "   .limit locals         1" << endl;
  *currentFile << "   aload_0" << endl;
  *currentFile << "   invokespecial         java/lang/Object/<init>()V" << endl;
  *currentFile << "   return" << endl;
  *currentFile << ".end method" << endl << endl;

  *currentFile << ".method                  public static readLineFunc()Ljava/lang/String;" << endl
	       << "   .limit stack          3" << endl
	       << "   .limit locals         2" << endl
	       << "   new                   java/util/Scanner" << endl
	       << "   dup                   " << endl
	       << "   getstatic             java/lang/System/in Ljava/io/InputStream;" << endl
	       << "   invokespecial         java/util/Scanner/<init>(Ljava/io/InputStream;)V" << endl
	       << "   astore_0              " << endl
	       << "   aload_0               " << endl
	       << "   invokevirtual         java/util/Scanner/nextLine()Ljava/lang/String;" << endl
	       << "   astore_1              " << endl
	       << "   aload_1               " << endl
	       << "   areturn               " << endl
	       << ".end method              " << endl << endl
	       << ".method                  public static readIntFunc()I" << endl
	       << "   .limit stack          3" << endl
	       << "   .limit locals         2" << endl
	       << "   new                   java/util/Scanner" << endl
	       << "   dup                   " << endl
	       << "   getstatic             java/lang/System/in Ljava/io/InputStream;" << endl
	       << "   invokespecial         java/util/Scanner/<init>(Ljava/io/InputStream;)V" << endl
	       << "   astore_0              " << endl
	       << "   aload_0               " << endl
	       << "   invokevirtual         java/util/Scanner/nextInt()I" << endl
	       << "   istore_1              " << endl
	       << "   iload_1               " << endl
	       << "   ireturn               " << endl
	       << ".end method" << endl;
}

void generate_class_preamble(string className, string superClassName, ParseTree * tree)
{
  *currentFile << ".class                   " << className << endl
               << ".super                   " 
               <<  (superClassName==""?"java/lang/Object":("_"+superClassName))
               << endl;
  if (tree->children[3]->children.size()!=0) {
    for (size_t i=0; i<tree->children[3]->children[1]->children.size(); i++) {
      *currentFile << ".implements              _" << tree->children[3]->children[1]->children[i]->token->text << endl;
    }
  }
  *currentFile << endl;
  bool classvars=false;
  for (size_t i=0; i<tree->children[4]->children.size(); i++) {
    if (tree->children[4]->children[i]->description=="variabledecl") {
      classvars=true;
      *currentFile << ".field                   " 
		   << tree->children[4]->children[i]->children[0]->children[1]->token->text;
      *currentFile << " " << decaf_type_to_jasmin_type(tree->children[4]->children[i]->children[0]->
						       children[0]->token->text) << endl;
    }
  }
  if (classvars)
    *currentFile << endl;

  *currentFile << ".method                  <init>()V" << endl;
  *currentFile << "   .limit stack          1" << endl;
  *currentFile << "   .limit locals         1" << endl;
  *currentFile << "   aload_0" << endl;
  if (superClassName=="")
    *currentFile << "   invokespecial         java/lang/Object/<init>()V" << endl;
  else
    *currentFile << "   invokespecial         _" << superClassName << "/<init>()V" << endl;
  *currentFile << "   return" << endl;
  *currentFile << ".end method" << endl;
}

void generate_main_java_function(string mainClassName)
{
  *currentFile << ".method                  public static main([Ljava/lang/String;)V" << endl;
  *currentFile << "   .limit stack          0" << endl;
  *currentFile << "   .limit locals         1" << endl;
  *currentFile << "   invokestatic          " << mainClassName << "/main()V" << endl;
  *currentFile << "   return                " << endl;
  *currentFile << ".end method " << endl << endl;
}

void generate_statement(ParseTree * statement)
{
  cout << "Generating statement..." << endl;
  if (statement->description=="stmt")
    generate_statement(statement->children[0]);
  else if (statement->description=="printstmt")
    generate_print(statement);
  else if (statement->description=="assign")
    generate_assign(statement);
  else if (statement->description=="returnstmt") {
    cout << "Generating returnstmt..." << endl;
    if (statement->children[1]!=NULL) {
      generate_expr(statement->children[1]);
      string type = statement->children[1]->stype;
      *currentFile << "   " << return_mnemonic(type) << endl;
    }
    else
      *currentFile << "   return" << endl;
  }
  else if (statement->description=="ifstmt")
    generate_ifstmt(statement);
  else if (statement->description=="whilestmt")
    generate_whilestmt(statement);
  else if (statement->description=="forstmt")
    generate_forstmt(statement);
  else if ((statement->description=="functioncall") or (statement->description=="methodcall"))
    generate_expr(statement);
  else if (statement->description=="breakstmt")
    generate_breakstmt();
  else if (statement->description=="stmtblock")
    generate_block(statement);
  else
    return;
}

void generate_block(ParseTree * block)
{
  cout << "Generating block..." << endl;
  Symtab *oldScope = currentScope;
  currentScope = block->symtab;
  ParseTree * statements = block->children[1];
  for (size_t i=0;i<statements->children.size();i++)
    generate_statement(statements->children[i]->children[0]);
  currentScope = oldScope;
}

string jasmin_formals(ParseTree * formals)
{
  string answer = "";
  for (size_t i=0;i<formals->children.size();i++) {
    ParseTree* var = formals->children[i];
    answer += decaf_type_to_jasmin_type(var->children[0]->token->text);
  }
  return "(" + answer + ")";
}

void generate_function(ParseTree * function)
{
  cout << "    Generating function : " << function->children[1]->token->text << endl;
  string functionName = function->children[1]->token->text;
  *currentFile << ".method                  public " << (currentClass==NULL?"static ":"")
	       << functionName
               << jasmin_formals(function->children[2]->children[0])
               << jasmin_type_from_tree(function->children[0]) << endl;
  *currentFile << "   .limit stack          10" << endl;
  *currentFile << "   .limit locals         10" << endl;
  if (functionName=="main") {
    *currentFile << "   new                   _read" << endl
		 << "   dup                   " << endl
		 << "   invokespecial         _read/<init>()V" << endl
		 << "   astore_1              " << endl
		 << "   .line                 17" << endl
		 << "   aload_1               " << endl
		 << "   invokevirtual         _read/initialize()V" << endl;
  }
  generate_block(function->children[3]);
  size_t numStmts = function->children[3]->children[1]->children.size();
  if ((function->children[0]->token->type==T_Void) and ((numStmts==0) or (function->children[3]->children[1]->children[numStmts-1]
									  ->description!="returnstmt")))
    *currentFile << "   return" << endl;
  *currentFile << ".end method" << endl << endl;    
}

void generate_class(ParseTree * classdecl)
{
  string class_name = "_"+(classdecl->children[1]->token->text);
  cout << "    Generating class : " << class_name << endl;
  ofstream * topFile = new ofstream((class_name+".j").c_str());
  ofstream * temp = currentFile;
  currentFile = topFile;
  currentClass = (S_class*)currentScope->lookup(classdecl->children[1]->token->text);
  string super_class = "";
  if (classdecl->children[2]->children.size()==2)
    super_class = (classdecl->children[2]->children[1]->token->text);
  generate_class_preamble(class_name, super_class, classdecl);
  *currentFile << endl;
  string storeClassName = className;
  className = class_name;
  generate(classdecl->children[4]);
  const char * temp2 = ("jasmin "+class_name+".j").c_str();
  system(temp2);
  className = storeClassName;
  currentClass = NULL;
  currentFile = temp;
}

void generate_prototype(ParseTree * prototype) {
  cout << "Generating prototype..." << endl;
  string prototypeName = prototype->children[1]->token->text;
  *currentFile << ".method                  public abstract "
	       << prototypeName
               << jasmin_formals(prototype->children[2]->children[0])
               << jasmin_type_from_tree(prototype->children[0]) << endl;
  *currentFile << ".end method" << endl << endl;  
}

void generate_interface(ParseTree * interface)
{
  string interface_name = "_"+(interface->children[1]->token->text);
  cout << "    Generating interface : " << interface_name << endl;
  ofstream * topFile = new ofstream((interface_name+".j").c_str());
  ofstream * temp = currentFile;
  currentFile = topFile;
  currentInterface = (S_interface*)currentScope->lookup(interface->children[1]->token->text);

  *currentFile << ".interface               abstract " << interface_name << endl
               << ".super                   java/lang/Object"
               << endl << endl;

  for (size_t i=0; i<interface->children[2]->children.size(); i++) {
    generate_prototype(interface->children[2]->children[i]);
  }

  const char * temp2 = ("jasmin "+interface_name+".j").c_str();
  system(temp2);
  currentInterface = NULL;
  currentFile = temp;
}

void generate(ParseTree * tree)
{
  if (!tree)
    return;
  if (tree->description=="functiondecl")
    generate_function(tree);
  else if (tree->description=="classdecl")
    generate_class(tree);
  else if (tree->description=="interfacedecl")
    generate_interface(tree);
  else
    for (size_t i=0;i<tree->children.size();i++)
      generate(tree->children[i]);
}

int main(int argc, char **argv)
{
  /* Make sure there's a given file name */
  if (argc != 2) {
    cout << "USAGE: " << argv[0] << " FILE" << endl;
    exit(1);
  }       
  yyin = fopen(argv[1], "r");
  /* and that it exists and can be read */
  if (!yyin) {
    cout << argv[1] << ": No such file or file can't be opened for reading."
         << endl;
    exit(1);
  }

  yyparse();
  traverseTree(top,0,0);
  currentClass = NULL;
  currentInterface = NULL;
  currentFunction = NULL;
  // Semantics:

  //currentScope = NULL;
  openscope();
  initializeScope();
  cout << "Starting Pass 1..." << endl;
  pass1(top);
  cout << "Starting Pass 3/2..." << endl;
  passThreeHalves();
  cout << "Starting Pass 2..." << endl;
  pass2(top, currentScope);
  cout << "Starting Pass 3..." << endl;
  pass3(top, currentScope);
  
  cout << "Beginning code generation..." << endl;
  // Code generation
  
  className = string(argv[1]);
  className = "_" + className.substr(0,className.size()-6);  // strip .decaf
  sourceName = className;

  currentLabel = 0;
  ofstream * topClassFile = new ofstream((className+".j").c_str());
  currentClass = NULL;
  currentFile = topClassFile;
  generate_preamble(className, "", top);
  generate(top);
  generate_main_java_function(className);
  const char * temp = ("jasmin "+className+".j").c_str();
  system(temp);
  return 0;
}
