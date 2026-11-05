CXX  = g++
FLEX = flex++

all: compiler

Lexer.cpp: lexer.ll
	$(FLEX) lexer.ll

compiler: Lexer.cpp main.cpp Lexer.hpp tokens.hpp
	$(CXX) Lexer.cpp main.cpp -o compiler

run: compiler
	./compiler prueba

clean:
	rm -f compiler Lexer.cpp

.PHONY: all run clean
