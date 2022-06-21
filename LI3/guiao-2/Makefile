#Compiler
CC = gcc

#Compiler Flags
CCFLAGS = -Wall -g

#GLIB Flag
PKG_CONFIG = `pkg-config --cflags --libs glib-2.0`

#Source Files
SRC = src/*.c src/queries/*.c

#Object Files
OBJ = obj/main.o obj/parser.o obj/queriesAuxiliar.o obj/queries.o

all: main
	doxygen ./Doxyfile

main:
	$(CC) $(CCFLAGS) $(SRC) -o guiao-2 -g ${PKG_CONFIG}
#Needed for debugging
## cc `pkg-config --cflags glib-2.0` hello.c -o hello `pkg-config --libs glib-2.0`

clean: 
	rm -r guiao-2 obj/*.o docs/html docs/latex