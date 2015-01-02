#include <vector>
#include <stack>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tokentype.h" 

  /* we are building parse trees */
#define YYSTYPE ParseTree *

  /* prototype for yyerror, needed on my linux laptop */
int yyerror(const char * s);

using namespace std;

enum PTtype {TERMINAL, NONTERMINAL};

struct Symtab;

struct ParseTree {
  Symtab *symtab;
  PTtype type;
  string stype;
  string description;
  Token * token;
  vector<ParseTree *> children;
  ParseTree(string description);
  ParseTree(Token * tokp);
  void addChild(ParseTree * tree);
  string toString();
};


 
 extern Token *myTok;
 extern int yylineno;
 int yylex();


string base26(int x);

string seq2str(int seq, int depth);

void traverseTree(ParseTree * tree, int depth, int seq);

