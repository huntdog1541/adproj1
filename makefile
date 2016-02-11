CC = gcc
CFLAGS = -c -Wall

TARGET = Parser
MAIN = src/main
PARSER = src/parser
LEXER = src/lexer
GLOBAL = src/global.h
SYMBOL = src/symbol
ERROR = src/error



$(TARGET): Main.o parser.o lexer.o error.o symbol.o
	$(CC) -o $(TARGET) Main.o parser.o lexer.o error.o symbol.o

Main.o: $(MAIN).c $(GLOBAL)
	$(CC) $(CFLAGS) $(MAIN).c $(GLOBAL)

parser.o: $(PARSER).c $(PARSER).h
	$(CC) $(CFLAGS) $(PARSER).c $(PARSER).h

lexer.o: $(LEXER).c $(LEXER).h
	$(CC) $(CFLAGS) $(LEXER).c $(LEXER).h

error.o: $(ERROR).c $(ERROR).h
	$(CC) $(CFLAGS) $(ERROR).c $(ERROR).h

symbol.o: $(SYMBOL).c $(SYMBOL).h
	$(CC) $(CFLAGS) $(SYMBOL).c $(SYMBOL).h

.PHONY : clean

clean :
			-rm -f *.o *.gch Parser.exe
