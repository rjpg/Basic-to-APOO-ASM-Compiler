#FLAGS=-lfl -L /usr/X11R6/lib -lX11 -lm

FLAGS=-lfl -Wall


all: 
	bison -d -v gram.y
	flex -i trab.lex
	gcc -c lex.yy.c	
	gcc -c gram.tab.c
	gcc -c mem.c
	gcc -c estr.c
	gcc -c hash.c
	gcc -c tree.c
	gcc -c convert.c
	gcc -c main.c
	gcc -o trab gram.tab.o lex.yy.o mem.o estr.o hash.o  tree.c convert.o main.o ${FLAGS}


clean:	
	rm -f \#* *~ *.o *.out core* *.tab.?


