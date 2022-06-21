#Compiler
CC = gcc

#Compiler Flags
CCFLAGS = -Wall -g 

#Source Files
SRC = src/main.c src/parser.c src/arv.c 

#Object Files
OBJ = obj/main.o obj/parser.o obj/arv.o 

all: main
	doxygen Doxyfile

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

obj/arv.o: src/arv.c
	gcc -c src/arv.c -o obj/arv.o

obj/parser.o:  src/parser.c
	gcc -c src/parser.c -o obj/parser.o

main: obj/main.o obj/parser.o obj/arv.o 
	$(CC) $(CCFLAGS) $(OBJ) -o guiao-1

clean: 
	rm -r guiao-1 obj/*.o saida/*.csv *.out docs/html docs/latex


