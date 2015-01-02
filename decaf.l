  /* -*-Fundamental-*- */
  /* definitions */

keyword   void|int|double|bool|string|class|interface|null|this|extends|implements|for|while|if|else|return|break|New|NewArray|Print|ReadInteger|ReadLine

idsC  [A-Za-z]

idC  [A-Za-z0-9_]

tidtrail  [[:space:]]*\[[[:space:]]*\]|[[:space:]]+{idsC}{idC}*

%{

#include <iostream>

using namespace std;

#include "tokentype.h"

string resultString;
Token* myTok;
int lineNum;
int length;

int error(string msg, int line)
{
  cout << msg << " on line " << line << endl;
  return -1;
}

int textLength(char *text)
{
  int length = 0;
  while (*text != 0) {
    length++;
    text++;
  }
  return length;
}

TokenType makeToken(TokenType type) {
    myTok = new Token(type, yytext, yylineno);
    return type;
}


%}

%option yylineno
%x STRING
%x COMMENT
%x COMMENT_2

%%

  /* rules */


  /* keywords */
void/{tidtrail}?        { return makeToken(T_Void); }
int/{tidtrail}?         { return makeToken(T_Int); }
double/{tidtrail}?      { return makeToken(T_Double); }
bool/{tidtrail}?        { return makeToken(T_Bool); }
string/{tidtrail}?      { return makeToken(T_String); }
class/{tidtrail}?       { return makeToken(T_Class); }
interface/{tidtrail}?   { return makeToken(T_Interface); }
null/{tidtrail}?        { return makeToken(T_Null); }
this/{tidtrail}?        { return makeToken(T_This); }
extends/{tidtrail}?     { return makeToken(T_Extends); }
implements/{tidtrail}?  { return makeToken(T_Implements); }
for/{tidtrail}?         { return makeToken(T_For); }
while/{tidtrail}?       { return makeToken(T_While); }
if/{tidtrail}?          { return makeToken(T_If); }
else/{tidtrail}?        { return makeToken(T_Else); }
return/{tidtrail}?      { return makeToken(T_Return); }
break/{tidtrail}?       { return makeToken(T_Break); }
New/{tidtrail}?         { return makeToken(T_New); }
NewArray/{tidtrail}?    { return makeToken(T_NewArray); }
Print/{tidtrail}?       { return makeToken(T_Print); }
ReadInteger/{tidtrail}? { return makeToken(T_ReadInteger); }
ReadLine/{tidtrail}?    { return makeToken(T_ReadLine); }


  /* other */
\+   { return makeToken(T_Plus); }
\-   { return makeToken(T_Minus); }
\*   { return makeToken(T_Times); }
\/   { return makeToken(T_Divide); }
\%   { return makeToken(T_Mod); }
\<   { return makeToken(T_Less); }
\<\= { return makeToken(T_LessEqual); }
\>   { return makeToken(T_Greater); }
\>\= { return makeToken(T_GreaterEqual); }
\=   { return makeToken(T_Assign); }
\=\= { return makeToken(T_Equal); }
\!\= { return makeToken(T_NotEqual); }
\&\& { return makeToken(T_And); }
\|\| { return makeToken(T_Or); }
\!   { return makeToken(T_Not); }
\;   { return makeToken(T_Semicolon); }
\,   { return makeToken(T_Comma); }
\.   { return makeToken(T_Dot); }
\[   { return makeToken(T_LBracket); }
\]   { return makeToken(T_RBracket); }
\(   { return makeToken(T_LParen); }
\)   { return makeToken(T_RParen); }
\{   { return makeToken(T_LBrace); }
\}   { return makeToken(T_RBrace); }


  /* boolean */
(true|false) { return makeToken(T_BoolConstant); }


  /* identifier */
{idsC}{idC}*/([[:space:]]+{keyword})? { if (textLength(yytext) < 32) {
		  return makeToken(T_Identifier);
	       }
	       resultString = "identifier ";
	       resultString += yytext;
	       resultString += " too long";
	       return error(resultString, yylineno); }


  /* type identifier */
{idsC}{idC}*/{tidtrail} { if (textLength(yytext) < 32) {
		  return makeToken(T_TypeIdentifier);
	       }
	       resultString = "type identifier ";
	       resultString += yytext;
	       resultString += " too long";
	       return error(resultString, yylineno); }


  /* double */
[0-9]+\.[0-9]*([Ee][\+\-]?[0-9]+)? { return makeToken(T_DoubleConstant); }


  /* integer */
([0-9]+|0[Xx][0-9A-Fa-f]+) { return makeToken(T_IntConstant); }


  /* string */
\"              { BEGIN(STRING); resultString = "\""; }
<STRING>[^\n"]* { resultString += yytext; }
<STRING>\n      { return error("missing \" at end of string constant", 
		  yylineno-1); }
<STRING><<EOF>> { return error("missing \" at end of string constant", 
		  yylineno); } 
<STRING>\"      { BEGIN(INITIAL); 
	          myTok = new Token(T_StringConstant,resultString + "\"", 
                                  yylineno);
		  return T_StringConstant; }


  /* comment */
\/\*             { BEGIN(COMMENT); lineNum = yylineno; }
<COMMENT><<EOF>> { return error("missing /* for block comment beginning on line ", lineNum); }
<COMMENT>\*\/    { BEGIN(INITIAL); }
<COMMENT>(.|\n)  { }


\/\/ { BEGIN(COMMENT_2); }
<COMMENT_2>\n { BEGIN(INITIAL); }
<COMMENT_2>. { }

[[:space:]]+ { }

\n { }

.  { resultString = "Stray '"; resultString += yytext; resultString += "'";
   return error(resultString, yylineno); }

<<EOF>> { return -1; }

%%

  /* subroutines */

int yywrap(void) {
    return 1;  // makes it stop at EOF.
} 
