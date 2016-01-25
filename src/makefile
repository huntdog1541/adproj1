CC = gcc
CFLAGS = -c -Wall

TARGET = Parse

$(TARGET): main.o parse.o lexer.o error.o symbol.o
	$(CC) -o $(TARGET) main.o parse.o lexer.o error.o symbol.o

main.o: main.c global.h
	$(CC) $(CFLAGS) main.c global.h

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) parse.c parse.h

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) lexer.c lexer.h

error.o: error.c error.h
	$(CC) $(CFLAGS) error.c error.h

symbol.o: symbol.c symbol.h
	$(CC) $(CFLAGS) symbol.c symbol.h
