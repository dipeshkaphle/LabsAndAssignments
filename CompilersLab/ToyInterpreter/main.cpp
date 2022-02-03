#include "Expr.hpp"
#include "parser.hpp"
#include <iostream>
extern int yyparse();
extern std::vector<Expr *> exps;
extern FILE *yyin;
// extern YYSTYPE yylval;

int main(int argc, char **argv) {
  FILE *fp = stdin;
  if (argc >= 2) {
    fp = fopen(argv[1], "r");
  }
  yyin = fp;
  yyparse();
  // std::cout << exps.size();
  for (auto &exp : exps) {
    std::cout << exp->s_exp() << '\n';
  }
  return 0;
}
