#include <iostream>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

#include "semantics.h"
#include "parsetree.h"


Symtab * currentScope = NULL;
S_interface* currentInterface = NULL;
S_class* currentClass = NULL;
S_function* currentFunction = NULL;
int currentSeq = 0;

Symtab::Symtab(Symtab *p) : parent(p) {}

semantics * Symtab::lookup(string key) { 
  semantics *answer;
  return 
    (answer = local_lookup(key)) ? answer : 
    parent ? parent->lookup(key) : NULL;

}

semantics * Symtab::local_lookup(string key) { 
  return dict[key];
}

void Symtab::print(ostream & ostr) 
{
  
  for (Dictionary::iterator i = dict.begin(); i != dict.end(); i++) {
    semantics * value = i->second;
    ostr << i->first << " => " << (value==NULL?"NULL":value->kind()) << endl;
  }
  ostr << "Parent Scope..." << endl;
  if (parent)
    parent->print(ostr);
}

void Symtab::insert(string key, semantics * item) {
  assert (dict[key] == NULL);
  dict[key] = item;
}

void openscope()
{
  currentScope = new Symtab(currentScope);
}

Symtab *closescope()
{
  Symtab *v = currentScope;
  currentScope = currentScope->parent;
  return v;
}

string get_type_name(ParseTree *typetree)
{
  // Convert a tree representing a type to a string.
  // My descriptions for these always start with TYPE_.
  // Your mileage may vary.
  assert(typetree->description.substr(0,5)=="TYPE_");
  //cout << "In get type name with " << typetree->toString() << endl;
  // Arrays go to "[]",
  // User-defined things go to the identifier.
  // Built-ins are like TYPE_int, so strip off the TYPE_.
  if (typetree->description == "TYPE_userdef")
	return typetree->children[0]->token->text;
  else if (typetree->description == "TYPE_array")
	return get_type_name(typetree->children[0])+" []";
  else
	return typetree->description.substr(5);
}
