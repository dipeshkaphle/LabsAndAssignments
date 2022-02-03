
CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-function -std=c++17
PROGRAM=main
LEXFILE=lexer
YACCFILE=parser
MAINFILE=main

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
