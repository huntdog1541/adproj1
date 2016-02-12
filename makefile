CC = gcc
CFLAGS = -c -Wall

TARGET = Parser
MAIN = src/main
PARSER = src/parser
LEXER = src/lexer
GLOBAL = src/global.h
SYMBOL = src/symbol
ERROR = src/error



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

legal:
	./Parser testfiles/test1.txt
	./Parser testfiles/test2.txt
	./Parser testfiles/test3.txt
	./Parser testfiles/test4.txt

illegal1:
	./Parser testfiles/illegaltest1.txt

illegal2:
	./Parser testfiles/illegaltest2.txt

illegal3:
	./Parser testfiles/illegaltest3.txt

illegal4:
	./Parser testfiles/illegaltest4.txt

.PHONY : clean

clean :
			-rm -f *.o *.gch Parser.exe
