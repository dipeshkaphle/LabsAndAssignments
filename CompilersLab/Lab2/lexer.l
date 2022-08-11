%{
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "colors.h"
extern FILE* yyin;
struct Loc{
	int col =0;
	int line=0;
};
enum TokenType{
TLET,
TBOOL,
TIF,
TELSE,
TWHILE,
TDOT,
TID,
TNUM,
TFN,
TLPAREN,
TRPAREN,
TLCURLY,
TRCURLY,
TSEMICOLON,
TCOLON,
TDATA,
TEQUAL,
TCEQ,
TCNEQ,
TCLT,
TCLE,
TCGT,
TCGE,
TPLUS,
TMINUS,
TMUL,
TDIV,
TAND,
TOR,
TNOT
};


#define TOK(t) Token(t,std::string(yytext, yyleng))
#define INC l.col+=yyleng
Loc l;

struct Token{
	TokenType type;
	std::string lit;
	Loc location;
	Token(TokenType to, std::string literal): type(to),lit(literal), location(l){}
};


std::vector<Token> tokens;
std::unordered_map<TokenType,std::string> tokenMap = {
	{TLET, "TLET"},
	{TBOOL, "TBOOL"},
	{TIF, "TIF"},
	{TELSE, "TELSE"},
	{TWHILE, "TWHILE"},
	{TDOT, "TDOT"},
	{TID, "TID"},
	{TNUM, "TNUM"},
	{TFN, "TFN"},
	{TLPAREN, "TLPAREN"},
	{TRPAREN, "TRPAREN"},
	{TLCURLY, "TLCURLY"},
	{TRCURLY, "TRCURLY"},
	{TSEMICOLON, "TSEMICOLON"},
	{TCOLON, "TCOLON"},
	{TDATA, "TDATA"},
	{TEQUAL, "TEQUAL"},
	{TCEQ, "TCEQ"},
	{TCNEQ, "TCNEQ"},
	{TCLT, "TCLT"},
	{TCLE, "TCLE"},
	{TCGT, "TCGT"},
	{TCGE, "TCGE"},
	{TPLUS, "TPLUS"},
	{TMINUS, "TMINUS"},
	{TMUL, "TMUL"},
	{TDIV, "TDIV"},
	{TAND, "TAND"},
	{TOR, "TOR"},
	{TNOT, "TNOT"}
};

extern "C" int yywrap() { return 1;}
bool hasError = false;
%}

%%

[ \t]                   { l.col++;}
[\n]                    { l.line++; l.col=0;}
"let"					{ INC; tokens.push_back(TOK(TLET));}
"data"					{ INC; tokens.push_back(TOK(TDATA));}
"true"					{ INC; tokens.push_back(TOK(TBOOL));}
"false"					{ INC; tokens.push_back(TOK(TBOOL));}
"if" 					{ INC; tokens.push_back(TOK(TIF));}
"else" 					{ INC; tokens.push_back(TOK(TELSE));}
"while"					{ INC; tokens.push_back(TOK(TWHILE));}
"fn"					{ INC; tokens.push_back(TOK(TFN));}
"and"                   { INC; tokens.push_back(TOK(TAND));}
"or"                    { INC; tokens.push_back(TOK(TOR));}
"." 					{ INC; tokens.push_back(TOK(TDOT));}
[_a-zA-z][_a-zA-Z0-9']* { INC; tokens.push_back(TOK(TID));}
[0-9]+\.[0-9]*          { INC; tokens.push_back(TOK(TNUM));}
[0-9]+                  { INC; tokens.push_back(TOK(TNUM));}
"("                     { INC; tokens.push_back(TOK(TLPAREN));}
")"                     { INC; tokens.push_back(TOK(TRPAREN));}
"{"                     { INC; tokens.push_back(TOK(TLCURLY));}
"}"                     { INC; tokens.push_back(TOK(TRCURLY));}
";"					    { INC; tokens.push_back(TOK(TSEMICOLON));}
":" 					{ INC; tokens.push_back(TOK(TCOLON));}
"="                     { INC; tokens.push_back(TOK(TEQUAL));}
"=="                    { INC; tokens.push_back(TOK(TCEQ));}
"!="                    { INC; tokens.push_back(TOK(TCNEQ));}
"!"						{ INC; tokens.push_back(TOK(TNOT)); }
"<"                     { INC; tokens.push_back(TOK(TCLT));}
"<="                    { INC; tokens.push_back(TOK(TCLE));}
">"                     { INC; tokens.push_back(TOK(TCGT));}
">="                    { INC; tokens.push_back(TOK(TCGE));}
"+"                     { INC; tokens.push_back(TOK(TPLUS));}
"-"                     { INC; tokens.push_back(TOK(TMINUS));}
"*"                     { INC; tokens.push_back(TOK(TMUL));}
"/"                     { INC; tokens.push_back(TOK(TDIV));}
.                       { std::cerr << RED << "Unknown input " << BOLDRED << std::string(yytext,yyleng) << " at Line : " << l.line << " and Col : " << l.col << RESET << std::endl; 
							hasError = true; 
							yyterminate();
						}
%%

int main(){
	yyin = fopen("input.txt","r");
	yylex();
	if(hasError) {
		std::cerr << RED << "Error in parsing" << RESET << std::endl;
		return 1;
	}
	bool show_lines=true;
	for(auto &x: tokens){
		std::cout<< BOLDWHITE << "Lexeme: "<< BOLDMAGENTA <<x.lit << WHITE <<", Token: " << BOLDMAGENTA << tokenMap.at(x.type) << RESET;
		if(show_lines){
			std::cout << " [at line: "<< CYAN << x.location.line << RESET << " and col: " << CYAN << x.location.col << RESET << "]\n";
		}else{
			std::cout<<"\n";
		}
	}
}
