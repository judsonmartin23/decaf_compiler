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
void pass1(ParseTree *tree);
void passThreeHalves();
void pass2(ParseTree* tree, Symtab* scope);
void pass3(ParseTree* tree, Symtab* scope);
void error_if_defined_locally(ParseTree *tree);
void initializeScope();


template <typename A, typename B, typename C>
struct triple {
  A first;
  B second;
  C third;
  triple(const A & f, const B & s, const C & t): first(f),second(s),third(t) {};
};

typedef triple < string, string, int > sstriple;
