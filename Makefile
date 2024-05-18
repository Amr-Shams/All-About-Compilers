.DEFAULT_GOAL := run_and_build
EXECUTABLE= parser
build_flex:
	flex scanner.l
	g++ -o scanner lex.yy.c -lfl

run_flex: 
	./scanner

build_all:
	flex scanner.l
	bison -d parser.y
	g++ -o parser parser.tab.c lex.yy.c -lfl -std=c++11 common.c symbolTable.cpp

run_all:
	./parser

run_and_build:
	bison -d -o parser.tab.c parser.y
	flex -o lex.yy.c scanner.l
	g++ -Iutils -o parser parser.tab.c lex.yy.c common.c symbolTable.cpp  -std=c++11
	./parser < input.txt

debug: 
	bison -d -o parser.tab.c parser.y
	flex -o lex.yy.c scanner.l
	g++ -Iutils -o parser parser.tab.c lex.yy.c common.c symbolTable.cpp -std=c++11 -g
	lldb ./parser

clean:
	rm -f *.o

run: $(EXECUTABLE)
	$(if $(OUTPUT_FILE), ./$(EXECUTABLE) $(INPUT_FILE) > $(OUTPUT_FILE), ./$(EXECUTABLE) $(INPUT_FILE))
	$(if $(SYMBOL_TABLE), cp $(BUILD_DIR)/symbolTable.txt $(SYMBOL_TABLE),)