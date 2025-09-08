# Makefile for Lexical Analyzer (Flex + GCC)

CC = gcc
FLEX = flex
LEXER = lexer
SRC = lexer.l
OBJ = lex.yy.c

all: $(LEXER)

$(LEXER): $(SRC)
	$(FLEX) $(SRC)
	$(CC) $(OBJ) -o $(LEXER) -lfl

run: $(LEXER)
	./$(LEXER) test.c

clean:
	rm -f $(LEXER) $(OBJ)
