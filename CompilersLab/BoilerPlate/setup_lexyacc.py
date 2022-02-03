from optparse import OptionParser
from pathlib import Path
import os

parser = OptionParser()
parser.add_option("-o", "--output", default='main',
                  help="Output executable name")
parser.add_option("-l", "--lex", default='lexer',
                  help="Lex file name")
parser.add_option("-y", "--yacc", default='parser',
                  help="Yacc file name")
parser.add_option("-m", "--main", default='main',
                  help="Main file name")
parser.add_option("","--fprint",action="store_true" ,default=False, help="print to stdout")
(options, args) = parser.parse_args()

program_name = "main"

makefile= '''
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-function -std=c++17
PROGRAM={}
LEXFILE={}
YACCFILE={}
MAINFILE={}

# Since it is the first rule, it is what will get made if
# we call "make" with no arguments.
$(PROGRAM): $(YACCFILE).o $(LEXFILE).o $(MAINFILE).cpp
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(MAINFILE).cpp $(LEXFILE).o $(YACCFILE).o

# Bison generates a C++ source file and a C++ header file.
$(YACCFILE).hpp $(YACCFILE).cpp : $(YACCFILE).y
	bison -Wcounterexamples -d -o $(YACCFILE).cpp $(YACCFILE).y

# Flex generates just a C++ source file.
$(LEXFILE).cpp: $(LEXFILE).l
	flex -o $(LEXFILE).cpp $(LEXFILE).l

# The lex file includes the header from Bison.
$(LEXFILE).o: $(LEXFILE).cpp $(YACCFILE).hpp
	$(CXX) $(CXXFLAGS) -c $(LEXFILE).cpp

$(YACCFILE).o: $(YACCFILE).cpp
	$(CXX) $(CXXFLAGS) -c $(YACCFILE).cpp

# The following line makes "make" automatically clean up these
# files for you when they are no longer needed.
.INTERMEDIATE: $(YACCFILE).o $(LEXFILE).o $(LEXFILE).cpp $(YACCFILE).cpp

# Run "make clean" to clear all extra files.
clean:
	-rm -f *.o $(YACCFILE).cpp $(YACCFILE).hpp $(PROGRAM)

# Do "make run" to run your program... this is used in the submit system
run: $(PROGRAM)
	@./$(PROGRAM)

# This is how we tell make that these two targets aren't actual files.
.PHONY: clean run
'''.format(options.output,options.lex,options.yacc, options.main)


lex_boilerplate ='''
%{{
#include "{}.hpp"


extern "C" int yywrap() {{ return 1;}}
%}}

%%

[ \\t\\n]                 ;
.                       printf("Unknown token!n"); yyterminate();

%%

'''.format(options.yacc)

yacc_boilerplate = r'''
%{
    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %sn", s); }
%}


/* Represents the many different ways we can access our data */
%union {
}

/* Define terminals */

%token <> 

/* Define non terminals */

%type <> 

/* Define assoc and precedence */
%left 
%right
%nonassoc

/* start rule*/
%start 

%%

%%
'''

main_boilerplate = '''
#include "{}.hpp"
#include <iostream>
extern int yyparse();
extern FILE *yyin;

int main(int argc, char **argv) {{
  FILE *fp = stdin;
  if (argc >= 2) {{
    fp = fopen(argv[1], "r");
  }}
  yyin = fp;
  yyparse();
  

  return 0;
}}

'''.format(options.yacc)


lexfile = options.lex + ".l"
yaccfile = options.yacc + ".y"
mainfile = options.main + ".cpp"

if not os.path.isfile(lexfile):
	open(lexfile,'w').write(lex_boilerplate)
if not os.path.isfile(yaccfile):
	open(yaccfile,'w').write(yacc_boilerplate)
if not os.path.isfile(mainfile):
	open(mainfile,'w').write(main_boilerplate)


# Path(options.lex + ".l").touch()
# Path(options.yacc+  ".y").touch()
# Path(options.main+".cpp").touch()

ccls = '''g++
%h %hpp %cpp -std=c++17
'''

compile_flags= '''-std=c++17
'''
if not os.path.isfile('.ccls'):
    open('.ccls','w').write(ccls)
if not os.path.isfile('compile_flags.txt'):
    open('compile_flags.txt','w').write(compile_flags)

if not options.fprint:
    print(makefile)
else:
	open('Makefile','w').write(makefile)
