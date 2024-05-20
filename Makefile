.DEFAULT_GOAL := run_and_build
EXECUTABLE= parser
build_flex:
	flex scanner.l

build_yacc:
	bison -d parser.y

run_flex: 
	./scanner



run_and_build:
	bison -d -o parser.tab.c parser.y
	flex -o lex.yy.c scanner.l
	g++ -Iutils -o parser parser.tab.c lex.yy.c src/common.c src/symbolTable.cpp src/helpers.c  -std=c++11
	./parser < input.txt

debug: 
	bison -d -o parser.tab.c parser.y
	flex -o lex.yy.c scanner.l
	g++ -Iutils -o parser parser.tab.c lex.yy.c src/common.c src/symbolTable.cpp src/helpers.c -I include -std=c++11
	lldb ./parser

clean:
	rm -f *.o
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f lex.yy.c
	rm -f parser
	rm -f parser.output
