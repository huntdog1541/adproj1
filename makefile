CC = gcc
CFLAGS = -c -Wall

TARGET = Parser
MAIN = main
PARSER = parser
LEXER = lexer
GLOBAL = global.h
SYMBOL = symbol
ERROR = error

$(TARGET): main.o parser.o lexer.o error.o symbol.o
	$(CC) -o $(TARGET) main.o parser.o lexer.o error.o symbol.o

main.o: $(MAIN).c $(GLOBAL)
	$(CC) $(CFLAGS) $(MAIN).c $(GLOBAL)

parser.o: $(PARSER).c $(PARSER).h
	$(CC) $(CFLAGS) $(PARSER).c $(PARSER).h

lexer.o: $(LEXER).c $(LEXER).h
	$(CC) $(CFLAGS) $(LEXER).c $(LEXER).h

error.o: $(ERROR).c $(ERROR).h
	$(CC) $(CFLAGS) $(ERROR).c $(ERROR).h

symbol.o: $(SYMBOL).c $(SYMBOL).h
	$(CC) $(CFLAGS) $(SYMBOL).c $(SYMBOL).h

illegal: illegal1 illegal2 illegal3 illegal4

legal:
	./Parser test1.txt
	./Parser test2.txt
	./Parser test3.txt
	./Parser test4.txt

illegal1:
	./Parser illegaltest1.txt

illegal2:
	./Parser illegaltest2.txt

illegal3:
	./Parser illegaltest3.txt

illegal4:
	./Parser illegaltest4.txt

.PHONY : clean

clean :
			-rm -f *.o *.gch
