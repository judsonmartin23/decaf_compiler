#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 55 "decaf.y"
#include <vector>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tokentype.h"
#include "parsetree.h"

  /* we are building parse trees */
#define YYSTYPE ParseTree *

using namespace std;

 extern ParseTree *top;

 ParseTree* makeBinExp(ParseTree* s1, ParseTree* s4);
 stack<Token*> tokstack;
 
#line 42 "y.tab.c"
#define Y_Void 257
#define Y_Int 258
#define Y_Double 259
#define Y_Bool 260
#define Y_String 261
#define Y_Class 262
#define Y_Interface 263
#define Y_Null 264
#define Y_This 265
#define Y_Extends 266
#define Y_Implements 267
#define Y_For 268
#define Y_While 269
#define Y_If 270
#define Y_Else 271
#define Y_Return 272
#define Y_Break 273
#define Y_New 274
#define Y_NewArray 275
#define Y_Print 276
#define Y_ReadInteger 277
#define Y_ReadLine 278
#define Y_BoolConstant 279
#define Y_StringConstant 280
#define Y_IntConstant 281
#define Y_DoubleConstant 282
#define Y_Identifier 283
#define Y_TypeIdentifier 284
#define Y_Plus 285
#define Y_Minus 286
#define Y_Times 287
#define Y_Divide 288
#define Y_Mod 289
#define Y_Less 290
#define Y_LessEqual 291
#define Y_Greater 292
#define Y_GreaterEqual 293
#define Y_Assign 294
#define Y_Equal 295
#define Y_NotEqual 296
#define Y_And 297
#define Y_Or 298
#define Y_Not 299
#define Y_Semicolon 300
#define Y_Comma 301
#define Y_Dot 302
#define Y_LBracket 303
#define Y_RBracket 304
#define Y_LParen 305
#define Y_RParen 306
#define Y_LBrace 307
#define Y_RBrace 308
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    3,    8,    7,
    9,    9,    9,    9,    9,    9,    4,   12,    4,   13,
   13,   10,   10,   14,   14,   15,   15,   17,   16,   18,
   18,   20,   19,   21,   21,   22,   22,   24,    5,   23,
   23,   25,   25,   26,   26,   28,    6,   27,   29,   27,
   30,   30,   31,   31,   33,   33,   34,   34,   11,   35,
   35,   35,   39,   39,   39,   39,   43,   43,   43,   43,
   43,   32,   32,   48,   40,   36,   36,   50,   41,   37,
   51,   42,   38,   52,   46,   53,   47,   54,   45,   55,
   55,   44,   44,   57,   49,   49,   49,   49,   49,   49,
   60,   49,   61,   49,   62,   49,   63,   49,   64,   49,
   65,   49,   66,   49,   67,   49,   68,   49,   69,   49,
   70,   49,   71,   49,   72,   49,   73,   49,   74,   49,
   75,   49,   76,   49,   77,   49,   78,   49,   56,   56,
   56,   79,   59,   59,   80,   80,   58,   58,   58,   58,
   58,
};
short yylen[] = {                                         2,
    1,    1,    2,    1,    1,    1,    1,    2,    1,    2,
    1,    1,    1,    1,    1,    3,    6,    0,    7,    1,
    3,    1,    0,    1,    3,    1,    0,    0,    3,    1,
    0,    0,    3,    1,    0,    1,    2,    0,    8,    1,
    1,    1,    0,    1,    2,    0,    6,    6,    0,    7,
    1,    2,    1,    2,    1,    0,    1,    0,    4,    1,
    1,    1,    1,    1,    1,    1,    2,    1,    1,    1,
    1,    1,    1,    4,    4,    2,    4,    4,    2,    2,
    8,    2,    2,    0,    4,    0,    3,    0,    6,    1,
    3,    1,    0,    0,    4,    1,    1,    1,    1,    3,
    0,    4,    0,    4,    0,    4,    0,    4,    0,    4,
    0,    3,    0,    4,    0,    4,    0,    4,    0,    4,
    0,    4,    0,    4,    0,    4,    0,    4,    0,    3,
    0,    4,    0,    4,    0,    5,    0,    7,    1,    3,
    4,    1,    4,    6,    1,    0,    1,    1,    1,    1,
    1,
};
short yydefred[] = {                                      0,
   18,   11,   12,   13,   14,   38,   46,   15,    0,    0,
    2,    4,    5,    6,    7,    0,    0,    0,    0,    0,
    3,    8,    9,    0,    0,    0,    0,    0,   16,    0,
    0,   28,    0,   26,    0,   20,    0,    0,    0,    0,
    0,   32,    0,   30,   49,    0,    0,    0,   44,   10,
    0,    0,    0,   29,    0,    0,    0,    0,   47,   45,
    0,   17,   21,   19,   24,    0,   40,   41,    0,    0,
   36,    0,    0,   51,    0,    0,    0,   39,   37,    0,
    0,   52,  151,   98,    0,    0,    0,   84,   86,  135,
  137,   88,  131,  133,  149,  150,  147,  148,  111,  129,
    0,    0,   71,    0,   53,    0,   73,   60,   61,   62,
   72,   63,   64,   65,   66,    0,   68,   69,   70,    0,
    0,    0,    0,    0,   96,   99,    0,   25,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   54,   59,   67,   76,    0,  101,  103,
  105,  107,  109,  113,  117,  115,  119,  121,  123,  125,
  127,    0,    0,   80,   79,   83,   82,   94,    0,    0,
   48,    0,    0,    0,    0,   87,    0,    0,    0,    0,
    0,    0,    0,  100,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   50,    0,   78,   74,   85,
    0,    0,    0,  132,  134,   77,   75,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  141,    0,    0,  143,    0,  136,    0,    0,    0,
    0,    0,    0,   89,  144,    0,  138,   81,
};
short yydgoto[] = {                                       9,
   10,   11,   12,   13,   14,   15,   16,  102,   37,   38,
  103,   18,   39,   66,   33,   34,   41,   43,   44,   55,
   69,   70,   71,   19,   47,   48,   49,   20,   57,   75,
  104,  105,   76,  106,  107,  108,  109,  110,  111,  112,
  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,
  123,  134,  135,  138,  204,  124,  202,  125,  126,  186,
  187,  188,  189,  190,  141,  191,  193,  192,  194,  195,
  196,  197,  198,  142,  139,  140,  136,  137,  127,  205,
};
short yysindex[] = {                                   -117,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -117,
    0,    0,    0,    0,    0, -268, -283, -207, -207, -207,
    0,    0,    0, -219, -223, -201, -161, -199,    0,  -27,
  -27,    0, -158,    0, -171,    0, -283, -200, -191, -195,
 -207,    0, -193,    0,    0, -283, -186, -171,    0,    0,
 -190,  -27, -190,    0, -207,  -72, -207, -170,    0,    0,
  -27,    0,    0,    0,    0, -163,    0,    0, -160,  -72,
    0, -156,  -27,    0,  -27,  -14, -207,    0,    0,  -27,
 -154,    0,    0,    0, -152, -151, -150,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   22,    0,    0,  -14,    0, -145,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -143,    0,    0,    0,  -14,
  374,  -14,  -14, -114,    0,    0, -122,    0, -125, -116,
   22,   22,   22,   22, -102, -113, -105, -103,  -98,  -97,
   22,   22,  197,    0,    0,    0,    0,  -46,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -207,   22,    0,    0,    0,    0,    0,   22,  -74,
    0,  -71,  219,  241,  -70,    0, -207,   22,   22,  -78,
  -69, -233, -222,    0,  -14,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   22,   22,   22,    0,  -67,
  316,   22,  374,  -66,  -64,    0,   22,    0,    0,    0,
  -63,  336, -258,    0,    0,    0,    0, -233, -233, -222,
 -222, -222,   -8,   -8,   -8,   -8,  431,  450,  412,  393,
   22,    0,  450,   22,    0,  355,    0,  -27,  -56,  -61,
  374,   22, -231,    0,    0,  -54,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  236,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -53,    0, -254,    0,    0,  -36,
  -36,    0,  -34,    0,  -55,    0,    0,    0,  -35,    0,
    0,    0,    0,    0,    0,    0,    0,  -33,    0,    0,
    0,    0,    0,    0,    0,  -32,    0,    0,    0,    0,
 -149,    0,    0,    0,    0,  -25,    0,    0,    0,  -24,
    0,    0,  -36,    0, -104, -267,    0,    0,    0,  -36,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   43,    0, -256,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -26,
 -272,  -26,  -26,   87,    0,    0,    0,    0,    0,    0,
  -26,    0,    0,  -26,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -59,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  260,  109,    0,  -26,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   65,    0,
    0,    0, -240,  -18,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  277,  294,  131,
  153,  175,   14,  459,  471,  483,  493,  503, -107, -277,
  -23,    0,  513,    0,    0,    0,    0,    0,    0,    0,
 -228,  -17,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  280,  -11,  -31,    0,    0,  -22,  -15,    1,  -13,
   12,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  222,    0,    0,    0,  250,    0,    0,    0,
    0,  -85,    0,    0, -106,    0,    0,    0, -108,    0,
    0,    0,    0, -124,    0,    0,    0,    0,  -95,    0,
    0,    0,    0,    0,  127,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  145,   82,
};
#define YYTABLESIZE 819
short yytable[] = {                                      23,
   17,   25,   26,   27,   28,  143,  172,   36,   36,  175,
   17,  148,   27,  165,  167,  164,  166,   40,  144,   24,
  128,   50,  128,  128,   68,   54,  128,   92,  128,   63,
   58,   22,   93,   92,  147,   46,  173,  174,   68,   65,
   58,   72,  234,   93,   67,  182,  183,  239,   46,   74,
   36,   57,   27,  151,  152,  153,   17,   36,   67,   81,
   90,  128,   62,   82,   64,   90,  129,  201,  162,  163,
   17,   24,   91,  203,  247,   23,  217,   91,  216,  162,
  163,   30,  212,  203,   29,   45,    2,    3,    4,    5,
  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,
  228,  229,  230,   31,   32,   51,  233,   35,   42,   52,
   53,  236,    8,   56,   56,   56,   61,  246,   56,   56,
   56,   59,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   73,  203,   56,   77,  241,    1,
    2,    3,    4,    5,    6,    7,  199,   78,   80,   56,
   56,  130,  131,  132,  133,   56,  146,   56,   56,   55,
   55,  211,  145,   55,   55,   55,    8,   55,   55,   55,
   55,   55,   55,   55,   55,   55,   55,   55,   55,  168,
  170,   55,  169,  171,    1,    2,    3,    4,    5,  126,
  126,  177,  126,  126,   55,   55,  126,  176,  126,  178,
   55,  179,   55,   55,   72,   72,  180,  181,   72,   72,
   72,    8,   72,   72,   72,   72,   72,   72,   72,   72,
   72,   72,   72,   72,  185,  206,   72,  214,  207,  210,
    2,    3,    4,    5,  234,    1,  215,  231,  243,   72,
   72,  235,  237,  244,  245,   72,   10,   72,   72,   83,
   84,  248,   43,   85,   86,   87,    8,   88,   89,   90,
   91,   92,   93,   94,   95,   96,   97,   98,   23,   23,
   22,   99,   31,   93,   42,   35,  149,  150,  151,  152,
  153,   33,  146,   34,  100,   83,   84,  145,   93,   21,
  101,   79,   61,  162,  163,   90,   91,   60,   93,   94,
   95,   96,   97,   98,   23,  213,  200,   99,  114,  114,
  114,  114,  240,  114,  114,    0,    0,  114,    0,  114,
  100,    0,    0,    0,    0,    0,  101,  139,  139,  139,
  139,  139,  139,  139,  139,  139,  139,  139,  139,  139,
  139,    0,  139,  139,  139,  139,  139,  142,  139,  140,
  140,  140,  140,  140,  140,  140,  140,  140,  140,  140,
  140,  140,  140,    0,  140,  140,  140,  140,  140,  142,
  140,   97,   97,   97,   97,   97,   97,   97,   97,   97,
    0,   97,   97,   97,   97,    0,   97,   97,   97,   97,
   97,    0,   97,  130,  130,  130,  130,  130,  130,  130,
  130,  130,    0,  130,  130,  130,  130,    0,  130,  130,
    0,    0,  130,    0,  130,  106,  106,  106,  106,  106,
  106,  106,  106,  106,    0,  106,  106,  106,  106,    0,
  106,  106,    0,    0,  106,    0,  106,  108,  108,  108,
  108,  108,  108,  108,  108,  108,    0,  108,  108,  108,
  108,    0,  108,  108,    0,    0,  108,    0,  108,  110,
  110,  110,  110,  110,  110,  110,  110,  110,    0,  110,
  110,  110,  110,    0,  110,  110,    0,    0,  110,    0,
  110,  149,  150,  151,  152,  153,  154,  155,  156,  157,
    0,  158,  159,  160,  161,    0,    0,    0,  162,  163,
    0,    0,  184,  149,  150,  151,  152,  153,  154,  155,
  156,  157,    0,  158,  159,  160,  161,    0,    0,    0,
  162,  163,    0,    0,  208,  149,  150,  151,  152,  153,
  154,  155,  156,  157,    0,  158,  159,  160,  161,    0,
    0,    0,  162,  163,  112,  112,  209,    0,    0,  112,
  112,  112,  112,    0,  112,  112,  112,  112,    0,  112,
  112,  102,  102,  112,    0,  112,  102,  102,  102,  102,
    0,  102,  102,  102,  102,    0,  102,  102,  104,  104,
  102,    0,  102,  104,  104,  104,  104,    0,  104,  104,
  104,  104,    0,  104,  104,    0,    0,  104,    0,  104,
  149,  150,  151,  152,  153,  154,  155,  156,  157,    0,
  158,  159,  160,  161,    0,    0,    0,  162,  163,  232,
  149,  150,  151,  152,  153,  154,  155,  156,  157,    0,
  158,  159,  160,  161,    0,    0,  238,  162,  163,  149,
  150,  151,  152,  153,  154,  155,  156,  157,    0,  158,
  159,  160,  161,    0,  242,    0,  162,  163,  149,  150,
  151,  152,  153,  154,  155,  156,  157,    0,  158,  159,
  160,  161,    0,    0,    0,  162,  163,  149,  150,  151,
  152,  153,  154,  155,  156,  157,    0,  158,  159,  160,
    0,    0,    0,    0,  162,  163,  149,  150,  151,  152,
  153,  154,  155,  156,  157,    0,  158,  159,    0,    0,
    0,    0,    0,  162,  163,  149,  150,  151,  152,  153,
  154,  155,  156,  157,    0,    0,  159,    0,    0,    0,
    0,    0,  162,  163,  149,  150,  151,  152,  153,  154,
  155,  156,  157,    0,    0,    0,    0,    0,    0,    0,
    0,  162,  163,  118,  118,  118,  118,    0,  118,  118,
    0,    0,  118,    0,  118,  116,  116,  116,  116,    0,
  116,  116,    0,    0,  116,    0,  116,  120,  120,  120,
  120,    0,  120,  120,    0,    0,  120,  122,  120,  122,
  122,    0,  122,  122,    0,    0,  122,  124,  122,  124,
  124,    0,  124,  124,    0,    0,  124,   95,  124,   95,
   95,    0,   95,   95,    0,    0,   95,    0,   95,
};
short yycheck[] = {                                     283,
    0,   17,   18,   19,   20,  101,  131,   30,   31,  134,
   10,  120,  267,  122,  123,  122,  123,   31,  104,  303,
  298,   37,  300,  301,   56,   41,  304,  300,  306,   52,
   46,  300,  300,  306,  120,   35,  132,  133,   70,   55,
  308,   57,  301,  300,   56,  141,  142,  306,   48,   61,
   73,  308,  307,  287,  288,  289,   56,   80,   70,   73,
  301,   77,   51,   75,   53,  306,   80,  163,  302,  303,
   70,  303,  301,  169,  306,  283,  185,  306,  185,  302,
  303,  305,  178,  179,  304,  257,  258,  259,  260,  261,
  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,
  196,  197,  198,  305,  266,  306,  202,  307,  267,  301,
  306,  207,  284,  307,  264,  265,  307,  242,  268,  269,
  270,  308,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  305,  231,  286,  301,  234,  257,
  258,  259,  260,  261,  262,  263,  162,  308,  305,  299,
  300,  306,  305,  305,  305,  305,  300,  307,  308,  264,
  265,  177,  308,  268,  269,  270,  284,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  294,
  306,  286,  305,  300,  257,  258,  259,  260,  261,  297,
  298,  305,  300,  301,  299,  300,  304,  300,  306,  305,
  305,  305,  307,  308,  264,  265,  305,  305,  268,  269,
  270,  284,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  271,  300,  286,  306,  300,  300,
  258,  259,  260,  261,  301,    0,  306,  305,  238,  299,
  300,  306,  306,  300,  306,  305,  300,  307,  308,  264,
  265,  306,  308,  268,  269,  270,  284,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  306,
  306,  286,  307,  300,  308,  308,  285,  286,  287,  288,
  289,  307,  306,  308,  299,  264,  265,  306,  306,   10,
  305,   70,  307,  302,  303,  274,  275,   48,  277,  278,
  279,  280,  281,  282,  283,  179,  162,  286,  295,  296,
  297,  298,  231,  300,  301,   -1,   -1,  304,   -1,  306,
  299,   -1,   -1,   -1,   -1,   -1,  305,  285,  286,  287,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,   -1,  300,  301,  302,  303,  304,  305,  306,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,   -1,  300,  301,  302,  303,  304,  305,
  306,  285,  286,  287,  288,  289,  290,  291,  292,  293,
   -1,  295,  296,  297,  298,   -1,  300,  301,  302,  303,
  304,   -1,  306,  285,  286,  287,  288,  289,  290,  291,
  292,  293,   -1,  295,  296,  297,  298,   -1,  300,  301,
   -1,   -1,  304,   -1,  306,  285,  286,  287,  288,  289,
  290,  291,  292,  293,   -1,  295,  296,  297,  298,   -1,
  300,  301,   -1,   -1,  304,   -1,  306,  285,  286,  287,
  288,  289,  290,  291,  292,  293,   -1,  295,  296,  297,
  298,   -1,  300,  301,   -1,   -1,  304,   -1,  306,  285,
  286,  287,  288,  289,  290,  291,  292,  293,   -1,  295,
  296,  297,  298,   -1,  300,  301,   -1,   -1,  304,   -1,
  306,  285,  286,  287,  288,  289,  290,  291,  292,  293,
   -1,  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,
   -1,   -1,  306,  285,  286,  287,  288,  289,  290,  291,
  292,  293,   -1,  295,  296,  297,  298,   -1,   -1,   -1,
  302,  303,   -1,   -1,  306,  285,  286,  287,  288,  289,
  290,  291,  292,  293,   -1,  295,  296,  297,  298,   -1,
   -1,   -1,  302,  303,  285,  286,  306,   -1,   -1,  290,
  291,  292,  293,   -1,  295,  296,  297,  298,   -1,  300,
  301,  285,  286,  304,   -1,  306,  290,  291,  292,  293,
   -1,  295,  296,  297,  298,   -1,  300,  301,  285,  286,
  304,   -1,  306,  290,  291,  292,  293,   -1,  295,  296,
  297,  298,   -1,  300,  301,   -1,   -1,  304,   -1,  306,
  285,  286,  287,  288,  289,  290,  291,  292,  293,   -1,
  295,  296,  297,  298,   -1,   -1,   -1,  302,  303,  304,
  285,  286,  287,  288,  289,  290,  291,  292,  293,   -1,
  295,  296,  297,  298,   -1,   -1,  301,  302,  303,  285,
  286,  287,  288,  289,  290,  291,  292,  293,   -1,  295,
  296,  297,  298,   -1,  300,   -1,  302,  303,  285,  286,
  287,  288,  289,  290,  291,  292,  293,   -1,  295,  296,
  297,  298,   -1,   -1,   -1,  302,  303,  285,  286,  287,
  288,  289,  290,  291,  292,  293,   -1,  295,  296,  297,
   -1,   -1,   -1,   -1,  302,  303,  285,  286,  287,  288,
  289,  290,  291,  292,  293,   -1,  295,  296,   -1,   -1,
   -1,   -1,   -1,  302,  303,  285,  286,  287,  288,  289,
  290,  291,  292,  293,   -1,   -1,  296,   -1,   -1,   -1,
   -1,   -1,  302,  303,  285,  286,  287,  288,  289,  290,
  291,  292,  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  302,  303,  295,  296,  297,  298,   -1,  300,  301,
   -1,   -1,  304,   -1,  306,  295,  296,  297,  298,   -1,
  300,  301,   -1,   -1,  304,   -1,  306,  295,  296,  297,
  298,   -1,  300,  301,   -1,   -1,  304,  295,  306,  297,
  298,   -1,  300,  301,   -1,   -1,  304,  295,  306,  297,
  298,   -1,  300,  301,   -1,   -1,  304,  295,  306,  297,
  298,   -1,  300,  301,   -1,   -1,  304,   -1,  306,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 308
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Y_Void","Y_Int","Y_Double",
"Y_Bool","Y_String","Y_Class","Y_Interface","Y_Null","Y_This","Y_Extends",
"Y_Implements","Y_For","Y_While","Y_If","Y_Else","Y_Return","Y_Break","Y_New",
"Y_NewArray","Y_Print","Y_ReadInteger","Y_ReadLine","Y_BoolConstant",
"Y_StringConstant","Y_IntConstant","Y_DoubleConstant","Y_Identifier",
"Y_TypeIdentifier","Y_Plus","Y_Minus","Y_Times","Y_Divide","Y_Mod","Y_Less",
"Y_LessEqual","Y_Greater","Y_GreaterEqual","Y_Assign","Y_Equal","Y_NotEqual",
"Y_And","Y_Or","Y_Not","Y_Semicolon","Y_Comma","Y_Dot","Y_LBracket",
"Y_RBracket","Y_LParen","Y_RParen","Y_LBrace","Y_RBrace",
};
char *yyrule[] = {
"$accept : program",
"program : decls",
"decls : decl",
"decls : decls decl",
"decl : variabledecl",
"decl : functiondecl",
"decl : classdecl",
"decl : interfacedecl",
"variabledecl : variable Y_Semicolon",
"identifier : Y_Identifier",
"variable : type identifier",
"type : Y_Int",
"type : Y_Double",
"type : Y_Bool",
"type : Y_String",
"type : Y_TypeIdentifier",
"type : type Y_LBracket Y_RBracket",
"functiondecl : type identifier Y_LParen formals Y_RParen stmtblock",
"$$1 :",
"functiondecl : Y_Void $$1 identifier Y_LParen formals Y_RParen stmtblock",
"variablelist : variable",
"variablelist : variablelist Y_Comma variable",
"formals : variablelist",
"formals :",
"identifierlist : identifier",
"identifierlist : identifierlist Y_Comma identifier",
"nextends : extends",
"nextends :",
"$$2 :",
"extends : Y_Extends $$2 identifier",
"nimplements : implements",
"nimplements :",
"$$3 :",
"implements : Y_Implements $$3 identifierlist",
"nfields : fields",
"nfields :",
"fields : field",
"fields : fields field",
"$$4 :",
"classdecl : Y_Class $$4 identifier nextends nimplements Y_LBrace nfields Y_RBrace",
"field : variabledecl",
"field : functiondecl",
"nprototypes : prototypes",
"nprototypes :",
"prototypes : prototype",
"prototypes : prototypes prototype",
"$$5 :",
"interfacedecl : Y_Interface $$5 identifier Y_LBrace nprototypes Y_RBrace",
"prototype : type identifier Y_LParen formals Y_RParen Y_Semicolon",
"$$6 :",
"prototype : Y_Void $$6 identifier Y_LParen formals Y_RParen Y_Semicolon",
"variabledecls : variabledecl",
"variabledecls : variabledecls variabledecl",
"stmts : stmt",
"stmts : stmts stmt",
"nvariabledecls : variabledecls",
"nvariabledecls :",
"nstmts : stmts",
"nstmts :",
"stmtblock : Y_LBrace nvariabledecls nstmts Y_RBrace",
"open_stmt : open_if",
"open_stmt : open_while",
"open_stmt : open_for",
"matched_stmt : matched_if",
"matched_stmt : matched_while",
"matched_stmt : matched_for",
"matched_stmt : other_stmt",
"other_stmt : nexpr Y_Semicolon",
"other_stmt : printstmt",
"other_stmt : returnstmt",
"other_stmt : breakstmt",
"other_stmt : stmtblock",
"stmt : matched_stmt",
"stmt : open_stmt",
"commonif : Y_If Y_LParen expr Y_RParen",
"matched_if : commonif matched_stmt Y_Else matched_stmt",
"open_if : commonif stmt",
"open_if : commonif matched_stmt Y_Else open_stmt",
"commonwhile : Y_While Y_LParen expr Y_RParen",
"matched_while : commonwhile matched_stmt",
"open_while : commonwhile open_stmt",
"commonfor : Y_For Y_LParen nexpr Y_Semicolon expr Y_Semicolon nexpr Y_RParen",
"matched_for : commonfor matched_stmt",
"open_for : commonfor open_stmt",
"$$7 :",
"returnstmt : Y_Return $$7 nexpr Y_Semicolon",
"$$8 :",
"breakstmt : Y_Break $$8 Y_Semicolon",
"$$9 :",
"printstmt : Y_Print $$9 Y_LParen exprlist Y_RParen Y_Semicolon",
"exprlist : expr",
"exprlist : exprlist Y_Comma expr",
"nexpr : expr",
"nexpr :",
"$$10 :",
"expr : lvalue Y_Assign $$10 expr",
"expr : constant",
"expr : lvalue",
"expr : Y_This",
"expr : call",
"expr : Y_LParen expr Y_RParen",
"$$11 :",
"expr : expr Y_Plus $$11 expr",
"$$12 :",
"expr : expr Y_Minus $$12 expr",
"$$13 :",
"expr : expr Y_Times $$13 expr",
"$$14 :",
"expr : expr Y_Divide $$14 expr",
"$$15 :",
"expr : expr Y_Mod $$15 expr",
"$$16 :",
"expr : Y_Minus $$16 expr",
"$$17 :",
"expr : expr Y_Less $$17 expr",
"$$18 :",
"expr : expr Y_Greater $$18 expr",
"$$19 :",
"expr : expr Y_LessEqual $$19 expr",
"$$20 :",
"expr : expr Y_GreaterEqual $$20 expr",
"$$21 :",
"expr : expr Y_Equal $$21 expr",
"$$22 :",
"expr : expr Y_NotEqual $$22 expr",
"$$23 :",
"expr : expr Y_And $$23 expr",
"$$24 :",
"expr : expr Y_Or $$24 expr",
"$$25 :",
"expr : Y_Not $$25 expr",
"$$26 :",
"expr : Y_ReadInteger $$26 Y_LParen Y_RParen",
"$$27 :",
"expr : Y_ReadLine $$27 Y_LParen Y_RParen",
"$$28 :",
"expr : Y_New $$28 Y_LParen identifier Y_RParen",
"$$29 :",
"expr : Y_NewArray $$29 Y_LParen expr Y_Comma type Y_RParen",
"lvalue : identifier",
"lvalue : expr Y_Dot identifier",
"lvalue : expr Y_LBracket expr Y_RBracket",
"_identifier : identifier",
"call : _identifier Y_LParen actuals Y_RParen",
"call : expr Y_Dot _identifier Y_LParen actuals Y_RParen",
"actuals : exprlist",
"actuals :",
"constant : Y_IntConstant",
"constant : Y_DoubleConstant",
"constant : Y_BoolConstant",
"constant : Y_StringConstant",
"constant : Y_Null",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 606 "decaf.y"

int yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  return 0;
}


ParseTree* makeBinExp(ParseTree* s1, ParseTree* s4)
{
  ParseTree *result = new ParseTree("binexpr");
  ParseTree *oper = new ParseTree(tokstack.top());
  tokstack.pop();
  result->addChild(s1);
  result->addChild(oper);
  result->addChild(s4);
  return result;
}

/*
int main() {
  yyparse();
  traverseTree(top, 0, 0);
  //cout << top->toString() << endl;
  return 0;
}
*/
#line 644 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 90 "decaf.y"
{
   top = yyval = new ParseTree("program");
   yyval->addChild(yyvsp[0]);
}
break;
case 2:
#line 96 "decaf.y"
{
   top = yyval = new ParseTree("decls");
   yyval->addChild(yyvsp[0]);
   }
break;
case 3:
#line 100 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 4:
#line 106 "decaf.y"
{
   top = yyval = new ParseTree("decl");
   yyval->addChild(yyvsp[0]);
   }
break;
case 5:
#line 110 "decaf.y"
{
   top = yyval = new ParseTree("decl");
   yyval->addChild(yyvsp[0]);
   }
break;
case 6:
#line 114 "decaf.y"
{
   top = yyval = new ParseTree("decl");
   yyval->addChild(yyvsp[0]);
   }
break;
case 7:
#line 118 "decaf.y"
{
   top = yyval = new ParseTree("decl");
   yyval->addChild(yyvsp[0]);
   }
break;
case 8:
#line 123 "decaf.y"
{
   top = yyval = new ParseTree("variabledecl");
   yyval->addChild(yyvsp[-1]);
   }
break;
case 9:
#line 129 "decaf.y"
{
  top = yyval = new ParseTree(myTok);
 }
break;
case 10:
#line 134 "decaf.y"
{
   top = yyval = new ParseTree("variable");
   yyval->addChild(yyvsp[-1]);
   yyval->addChild(yyvsp[0]);
   }
break;
case 11:
#line 141 "decaf.y"
{ top = yyval = new ParseTree(myTok); }
break;
case 12:
#line 142 "decaf.y"
{ top = yyval = new ParseTree(myTok); }
break;
case 13:
#line 143 "decaf.y"
{ top = yyval = new ParseTree(myTok); }
break;
case 14:
#line 144 "decaf.y"
{ top = yyval = new ParseTree(myTok); }
break;
case 15:
#line 145 "decaf.y"
{ top = yyval = new ParseTree(myTok); }
break;
case 16:
#line 146 "decaf.y"
{ yyval = yyvsp[-2]; }
break;
case 17:
#line 149 "decaf.y"
{
   top = yyval = new ParseTree("functiondecl");
   yyval->addChild(yyvsp[-5]);
   yyval->addChild(yyvsp[-4]);
   yyval->addChild(yyvsp[-2]);
   yyval->addChild(yyvsp[0]);
   }
break;
case 18:
#line 156 "decaf.y"
{ tokstack.push(myTok); }
break;
case 19:
#line 156 "decaf.y"
{
   top = yyval = new ParseTree("functiondecl");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-4]);
   yyval->addChild(yyvsp[-2]);
   yyval->addChild(yyvsp[0]);
   }
break;
case 20:
#line 166 "decaf.y"
{
   top = yyval = new ParseTree("variablelist");
   yyval->addChild(yyvsp[0]);
   }
break;
case 21:
#line 170 "decaf.y"
{
   yyvsp[-2]->addChild(yyvsp[0]);
   yyval = yyvsp[-2];
   }
break;
case 22:
#line 176 "decaf.y"
{
   top = yyval = new ParseTree("formals");
   yyval->addChild(yyvsp[0]);
   }
break;
case 23:
#line 180 "decaf.y"
{
   top = yyval = new ParseTree("formals");
   yyval->addChild(new ParseTree("variablelist"));
   }
break;
case 24:
#line 186 "decaf.y"
{
   top = yyval = new ParseTree("identifierlist");
   yyval->addChild(yyvsp[0]);
   }
break;
case 25:
#line 190 "decaf.y"
{
   yyvsp[-2]->addChild(yyvsp[0]);
   yyval = yyvsp[-2];
   }
break;
case 26:
#line 196 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 27:
#line 197 "decaf.y"
{ top = yyval = new ParseTree("extends"); }
break;
case 28:
#line 200 "decaf.y"
{ tokstack.push(myTok); }
break;
case 29:
#line 200 "decaf.y"
{
   top = yyval = new ParseTree("extends");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[0]);
   }
break;
case 30:
#line 208 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 31:
#line 209 "decaf.y"
{ top = yyval = new ParseTree("implements"); }
break;
case 32:
#line 212 "decaf.y"
{ tokstack.push(myTok); }
break;
case 33:
#line 212 "decaf.y"
{
   top = yyval = new ParseTree("implements");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[0]);
   }
break;
case 34:
#line 220 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 35:
#line 221 "decaf.y"
{ top = yyval = new ParseTree("fields"); }
break;
case 36:
#line 224 "decaf.y"
{
   top = yyval = new ParseTree("fields");
   yyval->addChild(yyvsp[0]);
   }
break;
case 37:
#line 228 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 38:
#line 234 "decaf.y"
{ tokstack.push(myTok); }
break;
case 39:
#line 234 "decaf.y"
{
   top = yyval = new ParseTree("classdecl");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-5]);
   yyval->addChild(yyvsp[-4]);
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 40:
#line 245 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 41:
#line 246 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 42:
#line 249 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 43:
#line 250 "decaf.y"
{ top = yyval = new ParseTree("prototypes"); }
break;
case 44:
#line 253 "decaf.y"
{
   top = yyval = new ParseTree("prototypes");
   yyval->addChild(yyvsp[0]);
   }
break;
case 45:
#line 257 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 46:
#line 263 "decaf.y"
{ tokstack.push(myTok); }
break;
case 47:
#line 263 "decaf.y"
{
   top = yyval = new ParseTree("interfacedecl");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 48:
#line 272 "decaf.y"
{
   top = yyval = new ParseTree("prototype");
   yyval->addChild(yyvsp[-5]);
   yyval->addChild(yyvsp[-4]);
   yyval->addChild(yyvsp[-2]);
   }
break;
case 49:
#line 278 "decaf.y"
{ tokstack.push(myTok); }
break;
case 50:
#line 278 "decaf.y"
{
   top = yyval = new ParseTree("prototype");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-4]);
   yyval->addChild(yyvsp[-2]);
   }
break;
case 51:
#line 287 "decaf.y"
{
   top = yyval = new ParseTree("variabledecls");
   yyval->addChild(yyvsp[0]);
   }
break;
case 52:
#line 291 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 53:
#line 297 "decaf.y"
{
   top = yyval = new ParseTree("stmts");
   yyval->addChild(yyvsp[0]);
   }
break;
case 54:
#line 301 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 55:
#line 307 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 56:
#line 308 "decaf.y"
{ top = yyval = new ParseTree("variabledecls"); }
break;
case 57:
#line 311 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 58:
#line 312 "decaf.y"
{ top = yyval = new ParseTree("stmts"); }
break;
case 59:
#line 315 "decaf.y"
{
   top = yyval = new ParseTree("stmtblock");
   yyval->addChild(yyvsp[-2]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 60:
#line 322 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 61:
#line 323 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 62:
#line 324 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 63:
#line 326 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 64:
#line 327 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 65:
#line 328 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 66:
#line 329 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 67:
#line 331 "decaf.y"
{ yyval = yyvsp[-1]; }
break;
case 68:
#line 332 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 69:
#line 333 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 70:
#line 334 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 71:
#line 335 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 72:
#line 338 "decaf.y"
{
   top = yyval = new ParseTree("stmt");
   yyval->addChild(yyvsp[0]);
   }
break;
case 73:
#line 342 "decaf.y"
{
   top = yyval = new ParseTree("stmt");
   yyval->addChild(yyvsp[0]);
   }
break;
case 74:
#line 348 "decaf.y"
{
   top = yyval = new ParseTree("ifstmt");
   yyval->addChild(yyvsp[-1]);
   }
break;
case 75:
#line 353 "decaf.y"
{
   yyvsp[-3]->addChild(yyvsp[-2]);
   yyvsp[-3]->addChild(yyvsp[0]);
   yyval = yyvsp[-3];
   }
break;
case 76:
#line 359 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 77:
#line 363 "decaf.y"
{
   yyvsp[-3]->addChild(yyvsp[-2]);
   yyvsp[-3]->addChild(yyvsp[0]);
   yyval = yyvsp[-3];
   }
break;
case 78:
#line 370 "decaf.y"
{
   top = yyval = new ParseTree("whilestmt");
   yyval->addChild(yyvsp[-1]);
   }
break;
case 79:
#line 375 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 80:
#line 380 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 81:
#line 386 "decaf.y"
{
   top = yyval = new ParseTree("forstmt");
   yyval->addChild(yyvsp[-5]);
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 82:
#line 393 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 83:
#line 398 "decaf.y"
{
   yyvsp[-1]->addChild(yyvsp[0]);
   yyval = yyvsp[-1];
   }
break;
case 84:
#line 404 "decaf.y"
{ tokstack.push(myTok); }
break;
case 85:
#line 404 "decaf.y"
{
   top = yyval = new ParseTree("returnstmt");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-1]);
   }
break;
case 86:
#line 412 "decaf.y"
{ tokstack.push(myTok); }
break;
case 87:
#line 412 "decaf.y"
{
   top = yyval = new ParseTree("breakstmt");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   }
break;
case 88:
#line 419 "decaf.y"
{ tokstack.push(myTok); }
break;
case 89:
#line 419 "decaf.y"
{
   top = yyval = new ParseTree("printstmt");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-2]);
   }
break;
case 90:
#line 427 "decaf.y"
{
   top = yyval = new ParseTree("exprlist");
   yyval->addChild(yyvsp[0]);
   }
break;
case 91:
#line 431 "decaf.y"
{
   yyvsp[-2]->addChild(yyvsp[0]);
   yyval = yyvsp[-2];
   }
break;
case 92:
#line 436 "decaf.y"
{ yyval = yyvsp[0]; }
break;
case 93:
#line 437 "decaf.y"
{ yyval = NULL; }
break;
case 94:
#line 440 "decaf.y"
{ tokstack.push(myTok); }
break;
case 95:
#line 440 "decaf.y"
{
   top = yyval = new ParseTree("assign");
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[0]);
   }
break;
case 96:
#line 447 "decaf.y"
{
   top = yyval = yyvsp[0];
   }
break;
case 97:
#line 450 "decaf.y"
{
      top = yyval = yyvsp[0];
   }
break;
case 98:
#line 453 "decaf.y"
{
   top = yyval = new ParseTree("this");
   yyval->addChild(new ParseTree(myTok));
   }
break;
case 99:
#line 457 "decaf.y"
{
   top = yyval = yyvsp[0];
   }
break;
case 100:
#line 460 "decaf.y"
{
   top = yyval = yyvsp[-1];
   }
break;
case 101:
#line 463 "decaf.y"
{ tokstack.push(myTok); }
break;
case 102:
#line 463 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 103:
#line 466 "decaf.y"
{ tokstack.push(myTok); }
break;
case 104:
#line 466 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 105:
#line 469 "decaf.y"
{ tokstack.push(myTok); }
break;
case 106:
#line 469 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 107:
#line 472 "decaf.y"
{ tokstack.push(myTok); }
break;
case 108:
#line 472 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 109:
#line 475 "decaf.y"
{ tokstack.push(myTok); }
break;
case 110:
#line 475 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 111:
#line 478 "decaf.y"
{ tokstack.push(myTok); }
break;
case 112:
#line 478 "decaf.y"
{
   top = yyval = new ParseTree("unexpr");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[0]);
   }
break;
case 113:
#line 484 "decaf.y"
{ tokstack.push(myTok); }
break;
case 114:
#line 484 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 115:
#line 487 "decaf.y"
{ tokstack.push(myTok); }
break;
case 116:
#line 487 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 117:
#line 490 "decaf.y"
{ tokstack.push(myTok); }
break;
case 118:
#line 490 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 119:
#line 493 "decaf.y"
{ tokstack.push(myTok); }
break;
case 120:
#line 493 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 121:
#line 496 "decaf.y"
{ tokstack.push(myTok); }
break;
case 122:
#line 496 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 123:
#line 499 "decaf.y"
{ tokstack.push(myTok); }
break;
case 124:
#line 499 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 125:
#line 502 "decaf.y"
{ tokstack.push(myTok); }
break;
case 126:
#line 502 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 127:
#line 505 "decaf.y"
{ tokstack.push(myTok); }
break;
case 128:
#line 505 "decaf.y"
{
   top = yyval = makeBinExp(yyvsp[-3], yyvsp[0]);
   }
break;
case 129:
#line 508 "decaf.y"
{ tokstack.push(myTok); }
break;
case 130:
#line 508 "decaf.y"
{
   top = yyval = new ParseTree("unexpr");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[0]);
   }
break;
case 131:
#line 514 "decaf.y"
{ tokstack.push(myTok); }
break;
case 132:
#line 514 "decaf.y"
{
   top = yyval = new ParseTree("readinteger");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   }
break;
case 133:
#line 519 "decaf.y"
{ tokstack.push(myTok); }
break;
case 134:
#line 519 "decaf.y"
{
   top = yyval = new ParseTree("readline");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   }
break;
case 135:
#line 524 "decaf.y"
{ tokstack.push(myTok); }
break;
case 136:
#line 524 "decaf.y"
{
   top = yyval = new ParseTree("new");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-1]);
   }
break;
case 137:
#line 530 "decaf.y"
{ tokstack.push(myTok); }
break;
case 138:
#line 530 "decaf.y"
{
   top = yyval = new ParseTree("expr");
   yyval->addChild(new ParseTree(tokstack.top()));
   tokstack.pop();
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 139:
#line 539 "decaf.y"
{
   top = yyval = new ParseTree("identifier");
   yyval->addChild(yyvsp[0]);
   }
break;
case 140:
#line 543 "decaf.y"
{
   top = yyval = new ParseTree("varacc");
   yyval->addChild(yyvsp[-2]);
   yyval->addChild(yyvsp[0]);
   }
break;
case 141:
#line 548 "decaf.y"
{
   top = yyval = new ParseTree("arracc");
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 142:
#line 555 "decaf.y"
{
   top = yyval = new ParseTree("identifier");
   yyval->addChild(yyvsp[0]);
   }
break;
case 143:
#line 561 "decaf.y"
{
   top = yyval = new ParseTree("functioncall");
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 144:
#line 566 "decaf.y"
{
   top = yyval = new ParseTree("methodcall");
   yyval->addChild(yyvsp[-5]);
   yyval->addChild(yyvsp[-3]);
   yyval->addChild(yyvsp[-1]);
   }
break;
case 145:
#line 574 "decaf.y"
{
   top = yyval = new ParseTree("actuals");
   yyval->addChild(yyvsp[0]);
   }
break;
case 146:
#line 578 "decaf.y"
{
   top = yyval = new ParseTree("actuals"); 
   yyval->addChild(new ParseTree("exprlist"));
   }
break;
case 147:
#line 584 "decaf.y"
{
   top = yyval = new ParseTree("constant");
   yyval->addChild(new ParseTree(myTok));
   }
break;
case 148:
#line 588 "decaf.y"
{
   top = yyval = new ParseTree("constant");
   yyval->addChild(new ParseTree(myTok));
   }
break;
case 149:
#line 592 "decaf.y"
{
   top = yyval = new ParseTree("constant");
   yyval->addChild(new ParseTree(myTok));
   }
break;
case 150:
#line 596 "decaf.y"
{
   top = yyval = new ParseTree("constant");
   yyval->addChild(new ParseTree(myTok));
   }
break;
case 151:
#line 600 "decaf.y"
{
   top = yyval = new ParseTree("constant");
   yyval->addChild(new ParseTree(myTok));
   }
break;
#line 1729 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
