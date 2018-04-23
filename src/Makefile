CC = gcc

CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o pretty.h pretty.o tree.h tree.o symbol.c symbol.o type.c type.o codegen.c codegen.o
	$(CC) lex.yy.o parser.tab.o pretty.o tree.o symbol.o type.o codegen.o main.o -o tiny -L/usr/local/opt/flex/lib -lfl

parser.tab.c parser.tab.h: tiny.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h tiny.y

lex.yy.c: tiny.l parser.tab.h
	flex tiny.l
clean:
	rm parser.tab.* lex.yy.*; rm *.o
