%{
#include <string>
#include "Expr.hpp"
#include "parser.hpp"

#define SAVE_STRING yylval.id = new std::string(yytext, yyleng)
#define TOKEN(t) ( yylval.token = t )
#define NUMBER yylval.number = std::stod(std::string(yytext,yyleng))
#define BOOL(b) yylval.bl = b 

extern "C" int yywrap() { return 1;}
%}

%%

[ \t\n]                 ;
"let"					return TLET;
"true"					BOOL(true); return TBOOL;
"false"					BOOL(false); return TBOOL;
[a-zA-z][a-zA-Z0-9']*   SAVE_STRING; return TID;
[0-9]+\.[0-9]*          NUMBER; return TNUM;
[0-9]+                  NUMBER; return TNUM;
"("                     return TLPAREN;
")"                     return TRPAREN;
";"						return TSEMICOLON;
"="                     return TEQUAL;
"=="                    TOKEN(EQ) ; return TCEQ;
"!="                    TOKEN(NEQ) ; return TCNEQ;
"<"                    TOKEN(LT) ; return TCLT;
"<="                    TOKEN(LE) ; return TCLE;
">"                    TOKEN(GT) ; return TCGT;
">="                    TOKEN(GE) ; return TCGE;
"+"                     TOKEN(PLUS); return TPLUS;
"-"                     TOKEN(MINUS); return TMINUS;
"*"                     TOKEN(MUL); return TMUL;
"/"                      TOKEN(DIV);return TDIV;
.                       printf("Unknown token!n"); yyterminate();

%%
