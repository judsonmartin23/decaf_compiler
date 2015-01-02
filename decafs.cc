#include "parsetree.h"
#include "semantics.h"
#include "assert.h"


extern int yyparse(void);
extern ParseTree * top;
extern Symtab * currentScope;
extern S_interface* currentInterface;
extern S_class* currentClass;
extern S_function* currentFunction;

void semantic_error(string err, int line);
S_variable * makeVariable(ParseTree *tree);
S_function * makeFunction(ParseTree *tree);
S_class * makeClass(ParseTree *tree);
S_interface * makeInterface(ParseTree *tree);
S_function * makePrototype(ParseTree *tree);
string get_type_name(ParseTree *typetree);
void mixed_arithmetic_type(ParseTree* temp);
bool classes_compatable(string t1, string t2, Symtab* scope);

int local_var_count;

enum var_sort {global, instance, local};

template <typename A, typename B, typename C>
struct triple {
  A first;
  B second;
  C third;
  triple(const A & f, const B & s, const C & t): first(f),second(s),third(t) {};
};

typedef triple < string, string, int > sstriple;

vector < sstriple > subsuprels;


void pass1(ParseTree * tree)
{
  if (!tree) return;
  if (tree->type==TERMINAL) return;
  if (tree->description=="stmtblock") {
    openscope();
    for (size_t i = 0; i < tree->children.size();i++)
      pass1(tree->children[i]);
    tree->symtab = closescope();
  }
  else if (tree->description=="variabledecl") {
    S_variable* var = makeVariable(tree->children[0]);
    if ((currentClass != NULL) and (currentFunction == NULL))
      currentClass->fields.push_back(var);
  }
  else if (tree->description=="functiondecl") {
    //cout << "In 'functiondecl'..." << endl;
    S_function* func = makeFunction(tree);
    if (currentInterface != NULL)
      currentInterface->functions.push_back(func);
    else if (currentClass != NULL)
      currentClass->fields.push_back(func);
  }
  else if (tree->description=="classdecl") {
    makeClass(tree);
  }
  else if (tree->description=="interfacedecl") {
    makeInterface(tree);
  }
  else if (tree->description=="prototype") {
    S_function* proto = makePrototype(tree);
    if (currentInterface != NULL)
      currentInterface->functions.push_back(proto);
    else if (currentClass != NULL)
      currentClass->fields.push_back(proto);
  }
  else if (tree->type==NONTERMINAL) {
    for (size_t i = 0; i < tree->children.size();i++)
      pass1(tree->children[i]);
  }
}


void passThreeHalves()
{
  for (size_t i = 0; i < subsuprels.size(); i++) {
    string sub = subsuprels[i].first;
    string sup = subsuprels[i].second;
    int line = subsuprels[i].third;
    S_class* subclass = (S_class*)(currentScope->lookup(sub));
    semantics* thing = (currentScope->lookup(sup));
    if (thing == NULL) {
      string error = "'" + sup + "' was never defined";
      semantic_error(error, line);
    }
    if (thing->kind() != "S_class") {
      string error = "'" + sup + "' must be defined as a class";
      semantic_error(error, line);
    }
    subclass->parentClass = (S_class*)thing;
    while (thing != NULL) {
      if ( (S_class*)thing == subclass ) {
	string error = "Class " + sub + " cannot extend itself";
	semantic_error(error, line);
      };
      thing = ((S_class*)thing)->parentClass;
    }
  }
}


void pass2(ParseTree* tree, Symtab* scope) {
  if (!tree) return;
  if (tree->symtab != NULL)
    scope = tree->symtab;
  if (tree->description=="variable") {
    if (scope->lookup(tree->children[0]->token->text) == NULL) {
      string error = "Type '" + (tree->children[0]->token->text) +
	"' is not defined";
      semantic_error(error, (tree->children[0]->token->line));
    }
    else if ((scope->lookup(tree->children[0]->token->text)->kind() !=
	     "S_class") and
	     (scope->lookup(tree->children[0]->token->text)->kind() !=
	      "S_interface")) {
      string error = "Type '" + (tree->children[0]->token->text) +
	"' is not defined as a class or interface";
      semantic_error(error, (tree->children[0]->token->line));
    }
  }
  else if (tree->description=="classdecl") {
    currentClass = (S_class*)scope->lookup(tree->children[1]->
						  token->text);
    pass2(tree->children[4], scope);
    if (tree->children[3]->children.size() == 2) {
      for (size_t b = 0; b < tree->children[3]->
	     children[1]->children.size(); b++) {
	if (scope->lookup(tree->children[3]->
				 children[1]->children[b]->
				 token->text) == NULL) {
	  string error = "Interface '" + (tree->children[3]->
					 children[1]->children[b]->
					 token->text) +
	    "' is never defined";
	  semantic_error(error, (tree->children[3]->
				 children[1]->children[b]->
				 token->line));
	}
	if (scope->lookup(tree->children[3]->
				 children[1]->children[b]->
				 token->text)->kind()
	    != "S_interface") {
	  string error = "'" + (tree->children[3]->
			  children[1]->children[b]->
			  token->text) +
	    "' is not defined as an interface";
	  semantic_error(error, (tree->children[3]->
				 children[1]->children[b]->
				 token->line));
	}
	S_interface* interface = (S_interface*)scope->
	  lookup(tree->children[3]->children[1]->children[b]->token->text);
	for (size_t i = 0; i < interface->functions.size(); i++) {
	  S_function* func;
	  if (scope->lookup(interface->functions[i]->name)
	      != NULL)
	    func = (S_function*)(scope->lookup(interface->functions[i]->name));
	  else if (scope->lookup(interface->functions[i]->name)
		   == NULL) {
	    S_class * thing = currentClass->parentClass;
	    bool found = false;
	    while ((thing != NULL) and (! found)) {
	      for (size_t x=0; x<thing->fields.size(); x++) {
		if (thing->fields[x]->kind() == "S_function") {
		  if (((S_function*)(thing->fields[x]))->name ==
		      ((S_function*)(interface->functions[i]))->name) {
		    found = true;
		    func = (S_function*)(thing->fields[x]);
		  }
		}
	      }
	      thing = thing->parentClass;
	    }
	    if (! found) {
	      string error = "Prototype '" + (interface->functions[i]->name) +
		"' is never defined";
	      semantic_error(error, (interface->functions[i]->line));
	    }
	  }
	  if (interface->functions[i]->returnType == NULL) {
	    if (func->returnType != NULL) {
	      string error = "Return type '" + (interface->functions[i]->
						returnType->name) +
		"' is incorrect";
	      semantic_error(error, (interface->functions[i]->line));
	    }
	  }
	  else if (interface->functions[i]->returnType->name !=
		   func->returnType->name) {
	    string error = "Return type '" + (interface->functions[i]->
					      returnType->name) +
	      "' is incorrect";
	    semantic_error(error, (interface->functions[i]->line));
	  }
	  if (interface->functions[i]->formals.size() != func->formals.size()) {
	    string error = "Prototype '" +
	      ((S_function*)(interface->functions[i]))->name +
	      "' has the wrong number of arguments";
	    semantic_error(error, tree->children[1]->token->line);
	  }
	  string t1;
	  string t2;
	  for (size_t x=0; x<func->formals.size(); x++) {
	    t1 = ((S_variable*)(interface->functions[i]->formals[x]))->
	      type->name;
	    t2 = ((S_variable*)(func->formals[x]))->type->name;
	    if (t1 != t2) {
	      string error = "Prototype '" +
		((S_function*)(interface->functions[i]))->name+
		"' has argument(s) of the wrong type";
	      semantic_error(error, (interface->functions[i]->line));
	    }
	  }
	}
	currentClass->interfaces.push_back(interface);
      }     
    }
    currentClass = NULL;
  }
  else if (tree->description=="functiondecl") {
    currentFunction = (S_function*)scope->lookup(tree->children[1]->
						  token->text);
    for (size_t i=2; i < tree->children.size(); i++)
      pass2(tree->children[i], scope);
    currentFunction = NULL;
  }
  else if (tree->description=="fields") {
    for (size_t i=0; i<tree->children.size(); i++) {
      if (tree->children[i]->description=="variabledecl") {
	S_class * thing = currentClass->parentClass;	
	while (thing != NULL) {
	  for (size_t x=0; x<thing->fields.size(); x++) {
	    if (thing->fields[x]->kind() == "S_variable") {
	      if (((S_variable*)(thing->fields[x]))->name ==
		  tree->children[i]->children[0]->children[1]->token->text) {
		string error = "Instance variable '" + 
		  (((S_variable*)(thing->fields[x]))->name) +
		  "' was previousy defined";
		semantic_error(error, (tree->children[i]->children[0]->
				       children[1]->token->line));
	      }
	    }
	  }
	  thing = thing->parentClass;
	}
      }
      else if (tree->children[i]->description=="functiondecl") {
	S_class * thing = currentClass->parentClass;
	bool found = false;
	S_function* func;
	while ((thing != NULL) and (! found)) {
	  for (size_t x=0; x<thing->fields.size(); x++) {
	    if (thing->fields[x]->kind() == "S_function") {
	      if (((S_function*)(thing->fields[x]))->name == tree->children[i]->
		  children[1]->token->text) {
		found = true;
		func = (S_function*)(thing->fields[x]);
	      }
	    }
	  }
	  thing = thing->parentClass;
	}
	if (found) {
	  if (func->returnType == NULL) {
	    if (tree->children[i]->children[0]->token->text != "void") {
	      string error = "Method '" + (func->name) +
		"' was previousy defined with return type 'void'";
	      semantic_error(error, (tree->children[i]->
				     children[1]->token->line));
	    }
	  }
	  else if (func->returnType->name !=
		   (tree->children[i]->children[0]->token->text)) {
	    string error = "Method '" +
	      (func->name) +
	      "' was previousy defined with return type '" +
	      (func->returnType->name) + "'";
	    semantic_error(error, (tree->children[i]->
				   children[1]->token->line));
	  }
	  if (tree->children[i]->children[2]->children[0]->children.size() !=
	      func->formals.size()) {
	    string error = "Method '" + tree->children[i]->children[1]->
	      token->text +
	      "' was previously defined with a different number of arguments";
	    semantic_error(error, tree->children[1]->token->line);
	  }
	  string t1;
	  string t2;
	  for (size_t b=0; b<func->formals.size(); b++) {
	    t1 = tree->children[i]->children[2]->children[0]->
	      children[b]->children[0]->token->text;
	    t2 = func->formals[b]->type->name;
	    if (t1 != t2) {
	      string error = "Method '" +
		tree->children[i]->children[1]->token->text +
		"' was previously defined with arguments of different type";
	      semantic_error(error, (tree->children[i]->children[1]->
				     token->line));
	    }
	  }
	}
	for (size_t i=2; i < tree->children.size(); i++)
	  pass2(tree->children[i], scope);
      }
    }
  }
  else if (tree->type==NONTERMINAL) {
    for (size_t i = 0; i < tree->children.size();i++)
      pass2(tree->children[i], scope);
  }
}


void pass3(ParseTree* tree, Symtab* scope) {
  if (!tree) return;
  if (tree->symtab != NULL)
    scope = tree->symtab;
  if (tree->description == "classdecl") {
    currentClass = (S_class*)(scope->lookup(tree->children[1]->
						   token->text));
    for (size_t i = 2; i < tree->children.size();i++)
      pass3(tree->children[i], scope);    
    currentClass = NULL;
  }
  else if (tree->description == "functiondecl") {
    currentFunction = (S_function*)(scope->lookup(tree->children[1]->
						   token->text));
    for (size_t i = 2; i < tree->children.size();i++)
      pass3(tree->children[i], scope);    
    currentFunction = NULL;
  }
  else if (tree->description == "readinteger")
    tree->stype = "int";
  else if (tree->description == "readline")
    tree->stype = "string";
  else if (tree->description == "constant") {
    int typeNum = tree->children[0]->token->type;
    if (typeNum == 279)
      tree->stype = "bool";
    else if (typeNum == 280)
      tree->stype = "string";
    else if (typeNum == 281)
      tree->stype = "int";
    else if (typeNum == 282)
      tree->stype = "double";
    else if (typeNum == 264)
      tree->stype = "null";
  }
  else if (tree->description=="new") {
    if (scope->lookup(tree->children[1]->token->text) == NULL) {
      string error = "Class '" + tree->children[1]->token->text +
	"' was never defined";
      semantic_error(error, (tree->children[0]->token->line));
    }
    if (scope->lookup(tree->children[1]->token->text)->kind() != "S_class") {
      string error = "'" + tree->children[1]->token->text +
	"' is not defined as a class";
      semantic_error(error, (tree->children[0]->token->line));
    }
    tree->stype = tree->children[1]->token->text;
  }
  else if (tree->description=="identifier") {
    if (scope->lookup(tree->children[0]->token->text) == NULL) {
      bool found = false;
      if ((currentClass != NULL) and (currentFunction != NULL)) {
	S_class* temp = currentClass->parentClass;
	while ((temp != NULL) and !(found)) {
	  for (size_t i=0; i<temp->fields.size(); i++) {
	    if (temp->fields[i]->kind() == "S_variable") {
	      if (((S_variable*)(temp->fields[i]))->name ==
		  tree->children[0]->token->text) {
		tree->stype = ((S_variable*)(temp->fields[i]))->type->name;
		found = true;
	      }
	    }
	  }
	  temp = temp->parentClass;
	}
      }
      if (! found) {
	string error = "Identifier '" + tree->children[0]->token->text +
	  "' was not defined in this scope";
	semantic_error(error, (tree->children[0]->token->line));
      }
    }
    else {
      string t1 = ((S_variable*)(scope->lookup(tree->children[0]->
					       token->text)))->type->name;
      tree->stype = t1;
    }
  }
  else if (tree->description == "binexpr") {
    pass3(tree->children[0], scope);
    pass3(tree->children[2], scope);
    string t1 = tree->children[0]->stype;
    string t2 = tree->children[2]->stype;
    if ((tree->children[1]->token->text == "==") or
	(tree->children[1]->token->text == "!=")) {
      bool matched = true;
      if (t2=="null") {
	if ((t1!="string") and
	    (t1!="bool") and
	    (t1!="int") and
	    (t1!="double"))
	  matched = true;
	else
	  matched = false;
      }
      else if (t1 != t2) {
	matched = false;
	S_class* thing = ((S_class*)(scope->lookup(t1)))->
	  parentClass;
	while ((thing != NULL) and (! matched)) {
	  if ( thing == (S_class*)(scope->lookup(t2)) ) {
	    matched = true;
	  }
	  thing = thing->parentClass;
	}
	thing = ((S_class*)(scope->lookup(t2)))->parentClass;
	while ((thing != NULL) and (! matched)) {
	  if ( thing == (S_class*)(scope->lookup(t1)) ) {
	    matched = true;
	  }
	  thing = thing->parentClass;
	}
      }
      if (! matched)
	mixed_arithmetic_type(tree);
      tree->stype = "bool";
    }
    else if ((tree->children[1]->token->text == "+") or
	     (tree->children[1]->token->text == "-")  or
	     (tree->children[1]->token->text == "*")  or
	     (tree->children[1]->token->text == "/")  or
	     (tree->children[1]->token->text == "%")) {
      if ((t1 != "int") and (t1 != "double"))
	mixed_arithmetic_type(tree);
      else if ( t1 != t2 ) {
	mixed_arithmetic_type(tree);
      }
      tree->stype = t1;
    }
    else if ((tree->children[1]->token->text == "<") or
	     (tree->children[1]->token->text == "<=")  or
	     (tree->children[1]->token->text == ">")  or
	     (tree->children[1]->token->text == ">=")) {
      if ((t1 != "int") and (t1 != "double"))
	mixed_arithmetic_type(tree);
      else if ( t1 != t2 )
	mixed_arithmetic_type(tree);
      tree->stype = "bool";
    }
    else if ((tree->children[1]->token->text == "&&") or
	     (tree->children[1]->token->text == "||")) {
      if (t1 != "bool") {
	mixed_arithmetic_type(tree);
      }
      else  if (t2 != "bool") {
	mixed_arithmetic_type(tree);
      }
      tree->stype = "bool";
    }
  }
  else if (tree->description=="this") {
    if (currentClass == NULL) {
      string error = "'this' can only exist within a class";
      semantic_error(error, (tree->children[0]->token->line));
    }
    tree->stype = currentClass->name;
  }
  else if (tree->description=="printstmt") {
    for (size_t i=0; i<tree->children[1]->children.size(); i++) {
      pass3(tree->children[1]->children[i], scope);
      if ( !((tree->children[1]->children[i]->stype == "int") or
	     (tree->children[1]->children[i]->stype == "bool") or
	     (tree->children[1]->children[i]->stype == "string"))) {
	string error = "'Print' does not take type '" +
	  tree->children[1]->children[i]->stype +
	  "'";
	semantic_error(error, (tree->children[0]->token->line));
      }  
    }
  }
  else if (tree->description=="unexpr") {
    pass3(tree->children[1], scope);
    string t1 = tree->children[1]->stype;
    if (tree->children[0]->token->text == "-") {
      if ((t1 != "int") and (t1 != "double")) {
	mixed_arithmetic_type(tree);
      }
      tree->stype = t1;
    }
    else if (tree->children[0]->token->text == "!") {
      if (t1 != "bool") {
	mixed_arithmetic_type(tree);
      }
      tree->stype = t1;
    }
  }
  else if (tree->description=="varacc") {
    pass3(tree->children[0], scope);
    if (scope->lookup(tree->children[0]->stype) == NULL) {
      string error = "Expression is not of a valid class";
      semantic_error(error, (tree->children[1]->token->line));
    }
    if (scope->lookup(tree->children[0]->stype)->kind() != "S_class") {
      string error = "Expression is not of a valid class";
      semantic_error(error, (tree->children[1]->token->line));
    }
    //if ((currentClass!=false) and (tree->children[0]->description!="this")) {
    //  string error = "Cannot access instance variable from within class";
    //  semantic_error(error, (tree->children[1]->token->line));
    //}
    S_class* thisClass = ((S_class *)(scope->lookup(tree->children[0]->stype)));
    bool found = false;
    S_variable* var;
    while ((thisClass != NULL) and (! found)) {
      for (size_t i=0; i<thisClass->fields.size(); i++) {
	if (thisClass->fields[i]->kind() == "S_variable") {
	  if (tree->children[1]->token->text ==
	      ((S_variable*)(thisClass->fields[i]))->name) {
	    var = (S_variable*)(thisClass->fields[i]);
	    found = true;
	  }
	}
      }
      thisClass = thisClass->parentClass;
    }
    if (! found) {
      string error = "Variable '" + tree->children[1]->token->text +
	"' is not a member of the class";
      semantic_error(error, tree->children[1]->token->line);
    }
    tree->stype = var->type->name;
  }
  else if (tree->description=="functioncall") {
    if (scope->lookup(tree->children[0]->children[0]->token->text) == NULL) {
      string error = "'" + tree->children[0]->children[0]->token->text +
	"' is not defined";
      semantic_error(error, tree->children[0]->children[0]->token->line);
    }
    if (scope->lookup(tree->children[0]->children[0]->token->text)->kind() != 
	"S_function") {
      string error = "'" + tree->children[0]->children[0]->token->text +
	"' is not defined as a function";
      semantic_error(error, tree->children[0]->children[0]->token->line);
    }
    S_function* func = (S_function*)(scope->lookup(tree->children[0]->
						   children[0]->token->text));
    if (tree->children[1]->children[0]->children.size() !=
	func->formals.size()) {
      string error = "Function '" + tree->children[0]->children[0]->
	token->text +
	"' has the wrong number of arguments";
      semantic_error(error, tree->children[0]->children[0]->token->line);
    }
    string t1;
    string t2;
    bool matched;
    for (size_t i=0; i<func->formals.size(); i++) {
      pass3(tree->children[1]->children[0]->children[i], scope);
      t1 = tree->children[1]->children[0]->children[i]->stype;
      t2 = func->formals[i]->type->name;
      if (t1 == "void") {
	string error = "Cannot use type 'void' as argument";
	semantic_error(error, (tree->children[0]->children[0]->token->line));
      }
      matched = classes_compatable(t1, t2, scope);
      if (! matched) {
	string error = "Function '" + tree->children[0]->children[0]->
	  token->text + "' has argument(s) of the wrong type";
	semantic_error(error, (tree->children[0]->children[0]->token->line));
      }
    }
    if (func->returnType == NULL)
      tree->stype = "void";
    else
      tree->stype = func->returnType->name;
  }
  else if (tree->description=="methodcall") {
    pass3(tree->children[0], scope);
    if (scope->lookup(tree->children[0]->stype) == NULL) {
      string error = "Method called on object that is not a class or interface";
      semantic_error(error, (tree->children[1]->children[0]->token->line));
    }
    bool found = false;
    S_function* func;
    if (scope->lookup(tree->children[0]->stype)->kind() == "S_class") {
      S_class* thisClass = (S_class*)(scope->lookup(tree->children[0]->stype));
      while ((thisClass != NULL) and (! found)) {
	for (size_t i=0; i<thisClass->fields.size(); i++) {
	  if (thisClass->fields[i]->kind() == "S_function") {
	    if (tree->children[1]->children[0]->token->text ==
		((S_function*)(thisClass->fields[i]))->name) {
	      func = (S_function*)(thisClass->fields[i]);
	      found = true;
	    }
	  }
	}
	thisClass = thisClass->parentClass;
      }
      if (! found) {
	string error = "Method '" + tree->children[1]->children[0]->
	  token->text + "' is not a member of the class";
	semantic_error(error, tree->children[1]->children[0]->token->line);
      }
    }
    else if (scope->lookup(tree->children[0]->stype)->kind() == "S_interface") {
      S_interface* thisInterface = (S_interface*)(scope->lookup(tree->
								children[0]->
								stype));
      for (size_t i=0; i<thisInterface->functions.size(); i++) {
	if (tree->children[1]->children[0]->token->text ==
	    ((S_function*)(thisInterface->functions[i]))->name) {
	  func = (S_function*)(thisInterface->functions[i]);
	  found = true;
	}
      }
      if (! found) {
	string error = "Method '" + tree->children[1]->children[0]->
	  token->text + "' is not a member of the interface";
	semantic_error(error, tree->children[1]->children[0]->token->line);
      }
    }
    else {
      string error = "Method called on object that is not a class or interface";
      semantic_error(error, (tree->children[1]->children[0]->token->line));
    }
    if (tree->children[2]->children[0]->children.size() !=
	func->formals.size()) {
      string error = "Method '" + tree->children[1]->children[0]->token->text +
	"' has the wrong number of arguments";
      semantic_error(error, tree->children[1]->children[0]->token->line);
    }
    string t1;
    string t2;
    bool matched;
    for (size_t i=0; i<func->formals.size(); i++) {
      pass3(tree->children[2]->children[0]->children[i], scope);
      t1 = tree->children[2]->children[0]->children[i]->stype;
      t2 = func->formals[i]->type->name;
      matched = classes_compatable(t1, t2, scope);
      if (! matched) {
	string error = "Method '" + tree->children[1]->children[0]->
	  token->text + "' has argument(s) of the wrong type";
	semantic_error(error, (tree->children[1]->children[0]->token->line));
      }
    }
    if (func->returnType == NULL)
      tree->stype = "void";
    else
      tree->stype = func->returnType->name;
  }
  else if (tree->description=="whilestmt") {
    pass3(tree->children[0], scope);
    pass3(tree->children[1], scope);
    if (tree->children[0]->stype != "bool") {
      string error = "While condition requires type 'bool'";
      ParseTree* temp = tree->children[0];
      while (temp->type==NONTERMINAL)
	temp = temp->children[0];
      semantic_error(error, (temp->token->line));
    }
  }
  else if (tree->description=="forstmt") {
    if (tree->children[0] != NULL) {
      pass3(tree->children[0], scope);
    }
    pass3(tree->children[1], scope);
    if (tree->children[1]->stype != "bool") {
      string error = "For condition requires type 'bool'";
      ParseTree* temp = tree->children[0];
      while (temp->type==NONTERMINAL)
	temp = temp->children[0];
      semantic_error(error, (temp->token->line));
    }
    if (tree->children[2] != NULL) {
      pass3(tree->children[2], scope);
    }
    pass3(tree->children[3], scope);
    
    //finish this later.....

  }
  else if (tree->description=="ifstmt") {
    pass3(tree->children[0], scope);
    pass3(tree->children[1], scope);
    if (tree->children.size() == 3)
      pass3(tree->children[2], scope);
    if (tree->children[0]->stype != "bool") {
      string error = "If condition requires type 'bool'";
      ParseTree* temp = tree->children[0];
      while (temp->type==NONTERMINAL)
	temp = temp->children[0];
      semantic_error(error, (temp->token->line));
    }
  }
  else if (tree->description=="assign") {
    pass3(tree->children[0], scope);
    pass3(tree->children[2], scope);
    string t1 = tree->children[0]->stype;
    string t2 = tree->children[2]->stype;
    if (t2 == "void") {
      string error = "Cannot assign type 'void'";
      semantic_error(error, (tree->children[1]->token->line));
    }
    bool matched = classes_compatable(t1, t2, scope);
    if (! matched) {
       string error = "Assignment type mismatch";
       semantic_error(error, (tree->children[1]->token->line));
    }
    tree->stype = t1;
  }
  else if (tree->description=="returnstmt") {
    if (tree->children[1] != NULL) {
      pass3(tree->children[1], scope);
      if (currentFunction->returnType == NULL) {
	string error = "Cannot return type '" + tree->children[1]->stype +
	  "' in void function";
	semantic_error(error, (tree->children[0]->token->line));
      }
      if (tree->children[1]->stype != currentFunction->returnType->name) {
	string error = "Type '" + tree->children[1]->stype +
	  "' is incorrect return type";
	semantic_error(error, (tree->children[0]->token->line));
      }
    }
    else if (currentFunction->returnType != NULL) {
      string error = "Must return type '" + currentFunction->returnType->name +
	"' in function";
      semantic_error(error, (tree->children[0]->token->line));
    }
  }
  else if (tree->type==NONTERMINAL) {
    for (size_t i = 0; i < tree->children.size();i++)
      pass3(tree->children[i], scope);
  }
}


bool classes_compatable(string t1, string t2, Symtab* scope) {
  bool matched = true;
  S_class* thing;
  if (t2=="null") {
    if ((t1!="string") and
	(t1!="bool") and
	(t1!="int") and
	(t1!="double"))
      return true;
    else
      return false;
  }
  if (t1 != t2) {
    matched = false;
    if (scope->lookup(t1)->kind() == "S_class") {
      thing = ((S_class*)(scope->lookup(t1)));
      while ((thing != NULL) and (! matched)) {
	if ( thing->name == t2 )
	  matched = true;
	for (size_t i=0; i<thing->interfaces.size(); i++) {
	  if (thing->interfaces[i]->name == t2)
	    matched = true;
	}
	thing = thing->parentClass;
      }
    }
    if (scope->lookup(t2)->kind() == "S_class") {
      thing = ((S_class*)(scope->lookup(t2)));
      while ((thing != NULL) and (! matched)) {
	if ( thing->name == t1 )
	  matched = true;
	for (size_t i=0; i<thing->interfaces.size(); i++) {
	  if (thing->interfaces[i]->name == t1)
	    matched = true;
	}
	thing = thing->parentClass;
      }
    }
  }
  return matched;
}


void mixed_arithmetic_type(ParseTree* tree) {
  
  string error = "Mixed arithmetic type";
  semantic_error(error, (tree->children[1]->token->line));
  
}


void semantic_error(string err, int line)
{
  cout << "Semantic error: " << err << " on line " << line << endl;
  exit(1);
}


void error_if_defined_locally(ParseTree *tree)
{
  assert(tree->type == TERMINAL and tree->token->type == T_Identifier);
  string var_name = tree->token->text;
  int lineno = tree->token->line;
  if (currentScope->local_lookup(var_name))
	semantic_error("'" + var_name + "' already defined", lineno);
}


S_function * makePrototype(ParseTree *tree)
{
  assert(tree->description == "prototype");
  error_if_defined_locally(tree->children[1]);
  string proto_name = tree->children[1]->token->text;
  S_function *entry = new S_function;
  entry->name = proto_name;
  entry->line = tree->children[1]->token->line;
  if (tree->children[0]->token->type !=  T_Void) {
    string type_name = tree->children[0]->token->text;
    entry->returnType = new S_type;
    entry->returnType->name = type_name;
  }
  openscope();

  if (tree->children[2]->children.size() != 0) {
    for (size_t i = 0; i < tree->children[2]->children[0]->children.size();i++)
      entry->formals.push_back(makeVariable(tree->children[2]->
					    children[0]->children[i]));
  }
  tree->symtab = closescope();
  currentScope->dict[proto_name] = entry;
  return entry;
}


S_interface * makeInterface(ParseTree *tree)
{
  assert(tree->description == "interfacedecl");
  error_if_defined_locally(tree->children[1]);
  string interface_name = tree->children[1]->token->text;
  S_interface *entry = new S_interface;
  entry->name = interface_name;
  currentInterface = entry;
  openscope();
  for (size_t i = 0; i < tree->children[2]->children.size();i++)
    pass1(tree->children[2]->children[i]);
  tree->symtab = closescope();
  currentScope->dict[interface_name] = entry;
  currentInterface = NULL;
  return entry;
}


S_class * makeClass(ParseTree *tree)
{
  assert(tree->description == "classdecl");
  error_if_defined_locally(tree->children[1]);
  string class_name = tree->children[1]->token->text;
  S_class *entry = new S_class;
  entry->name = class_name;
  currentClass = entry;
  openscope();
  for (size_t i = 0; i < tree->children[4]->children.size();i++)
    pass1(tree->children[4]->children[i]);
  tree->symtab = closescope();
  entry->parentClass = NULL;
  currentScope->dict[class_name] = entry;
  if (tree->children[2]->children.size() != 0) {
    string ident = tree->children[1]->token->text;
    string super = tree->children[2]->children[1]->token->text;
    int lineno = tree->children[0]->token->line;
    subsuprels.push_back(sstriple(ident, super, lineno));
  }
  currentClass = NULL;
  return entry;
}

int lineNumber(ParseTree * tree) {
  ParseTree * temp;
  while(tree->type!=TERMINAL) {
    temp = tree->children[0];
    tree = temp;
  }
  return tree->token->line;
}

S_function * makeFunction(ParseTree *tree)
{
  assert(tree->description == "functiondecl");
  error_if_defined_locally(tree->children[1]);
  string func_name = tree->children[1]->token->text;
  S_function *entry = new S_function;
  entry->name = func_name;
  entry->line = tree->children[1]->token->line;
  if (tree->children[0]->token->type !=  T_Void) {
    string type_name = tree->children[0]->token->text;
    entry->returnType = new S_type;
    entry->returnType->name = type_name;
  }
  else
    entry->returnType = NULL;
  currentFunction = entry;
  openscope();
  local_var_count = 0;

  if (tree->children[2]->children.size() != 0) {
    for (size_t i = 0; i < tree->children[2]->children[0]->children.size();i++)
      entry->formals.push_back(makeVariable(tree->children[2]->
					    children[0]->children[i]));
  }
  pass1(tree->children[3]);
  currentFunction = NULL;
  tree->symtab = closescope();
  currentScope->dict[func_name] = entry;
  return entry;
}


S_variable * makeVariable(ParseTree *tree)
{
  assert(tree->description == "variable");
  string var_name = tree->children[1]->token->text;
  string type_name = tree->children[0]->token->text;
  error_if_defined_locally(tree->children[1]);
  S_variable *entry = new S_variable;
  entry->type = new S_type;
  entry->type->name = type_name;
  entry->name = var_name;

  if (currentFunction != NULL) {
    if (currentClass != NULL)
      entry->number = local_var_count + 1;
    else
      entry->number = local_var_count;
    local_var_count++;
    entry->global = false;
    entry->instance = false;
  }
  else if (currentClass != NULL) {
    entry->instance = true;
    entry->global = false;
  }
  else {
    entry->global = true;
    entry->instance = false;
  }
  currentScope->dict[var_name] = entry;
  return entry;
}


void initializeScope() {
  S_class* intEntry = new S_class;
  intEntry->parentClass = NULL;
  currentScope->dict["int"] = intEntry;
  S_class* boolEntry = new S_class;
  boolEntry->parentClass = NULL;
  currentScope->dict["bool"] = boolEntry;
  S_class* stringEntry = new S_class;
  stringEntry->parentClass = NULL;
  currentScope->dict["string"] = stringEntry;
  S_class* doubleEntry = new S_class;
  doubleEntry->parentClass = NULL;
  currentScope->dict["double"] = doubleEntry;
}

/*
int main()
{
  yyparse();
  //traverseTree(top,0,0);
  openscope();
  initializeScope();
  //cout << "Starting Pass 1" << endl;
  pass1(top);
  //cout << "Starting Pass 3/2" << endl;
  passThreeHalves();
  //cout << "Starting Pass 2" << endl;
  pass2(top, currentScope);
  //cout << "Starting Pass 3" << endl;
  pass3(top, currentScope);
  exit(0);
  return 0;
}
*/
