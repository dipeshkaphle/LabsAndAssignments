%{
    #include "Operators.hpp"
    #include "Expr.hpp"
    #include <string>
    #include <vector>
    std::vector<Expr*> exps;
    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %sn", s); }
%}


/* Represents the many different ways we can access our data */
%union {
    Expr *expr;
    double number;
    bool bl;
    std::string* id;
	Op token;
}

/* Define terminals */

%token <number> TNUM
%token <bl> TBOOL
%token <id> TID
%token <token> TCEQ TCNEQ TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLET TSEMICOLON
%token <token> TPLUS TMINUS TMUL TDIV

/* Define non terminals */

%type <expr> expr comparision sum product term unary
%type <token> comparisionop

%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%
program: expr TSEMICOLON           {exps.push_back($<expr>1);}
       | program expr TSEMICOLON   {exps.push_back($<expr>2);}
       ;

expr : TLET TID TEQUAL expr {$$= new Assign(*$2,$4) ; delete $2; }
     | comparision                      {$$=$1; }
     ;

comparision: comparision comparisionop comparision      {$$=new BinaryExpr($1,$3,$<token>2); }
           | unary                {$$= $1;}
           ;

unary: TMINUS unary         {$$=new Neg($2);}
     | sum                  {$$=$1;}
     ;

sum: sum TPLUS sum              {$$=new BinaryExpr($1,$3,PLUS);}
    | sum TMINUS sum            {$$=new BinaryExpr($1,$3,MINUS);}
    | product                   {$$=$1;}
    ;

product: product TMUL product         { $$= new BinaryExpr($1,$3,MUL);}
       | product TDIV product   { $$= new BinaryExpr($1,$3,DIV);}
       | term                   {$$=$1;}
       ;


term : TLPAREN expr TRPAREN         {$$=$2;}
     | TNUM                         {$$= new Literal($<number>1);}
     | TBOOL                        {$$=new Literal($<bl>1);}
     | TID                          {$$= new Var(*$1);delete $1;}
     ;

comparisionop : TCNEQ | TCEQ | TCLT | TCLE | TCGT | TCGE
              ;

%%
