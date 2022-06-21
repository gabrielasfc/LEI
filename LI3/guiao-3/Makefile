#Compiler
CC = gcc

#Compiler Flags
CCFLAGS = -Wall -g -pg

#GLIB Flag
PKG_CONFIG = `pkg-config --cflags --libs glib-2.0`

#Source Files
SRC = src/cat_users.c src/cat_repos.c src/cat_commits.c src/main.c src/parser.c src/menus.c src/command_interpreter.c src/counter_hash.c src/queries/*

#Source Files for Testing Program
SRC_T = src/test_queries.c  src/queries/* src/counter_hash.c src/cat_users.c src/cat_commits.c src/cat_repos.c src/parser.c

#Object Files
OBJ = obj/main.o obj/cat_commits.o obj/cat_repos.o obj/cat_users.o obj/command_interpreter.o obj/counter_hash.o obj/menus.o obj/parser.o obj/query5.o obj/query6.o obj/query7.o obj/query8.o obj/query9.o obj/query10.o

OBJ_TEST = obj/test_queries.o obj/cat_commits.o obj/cat_repos.o obj/cat_users.o obj/command_interpreter.o obj/counter_hash.o obj/menus.o obj/parser.o obj/query5.o obj/query6.o obj/query7.o obj/query8.o obj/query9.o obj/query10.o

all: main tests

obj/main.o : src/main.c
		gcc -c src/main.c -o obj/main.o ${PKG_CONFIG}

obj/cat_commits.o : src/cat_commits.c
		gcc -c src/cat_commits.c -o obj/cat_commits.o ${PKG_CONFIG}

obj/cat_repos.o : src/cat_repos.c
		gcc -c src/cat_repos.c -o obj/cat_repos.o ${PKG_CONFIG}

obj/cat_users.o : src/cat_users.c
		gcc -c src/cat_users.c -o obj/cat_users.o ${PKG_CONFIG}

obj/command_interpreter.o : src/command_interpreter.c
		gcc -c src/command_interpreter.c -o obj/command_interpreter.o ${PKG_CONFIG}

obj/counter_hash.o : src/counter_hash.c
		gcc -c src/counter_hash.c -o obj/counter_hash.o ${PKG_CONFIG}

obj/menus.o : src/menus.c
		gcc -c src/menus.c -o obj/menus.o ${PKG_CONFIG}

obj/parser.o : src/parser.c
		gcc -c src/parser.c -o obj/parser.o ${PKG_CONFIG}

obj/test_queries.o : src/test_queries.c
		gcc -c src/test_queries.c -o obj/test_queries.o ${PKG_CONFIG}

obj/query5.o : src/queries/query5.c
		gcc -c src/queries/query5.c -o obj/query5.o ${PKG_CONFIG}

obj/query6.o : src/queries/query6.c
		gcc -c src/queries/query6.c -o obj/query6.o ${PKG_CONFIG}

obj/query7.o : src/queries/query7.c
		gcc -c src/queries/query7.c -o obj/query7.o ${PKG_CONFIG}

obj/query8.o : src/queries/query8.c
		gcc -c src/queries/query8.c -o obj/query8.o ${PKG_CONFIG}

obj/query9.o : src/queries/query9.c
		gcc -c src/queries/query9.c -o obj/query9.o ${PKG_CONFIG}

obj/query10.o : src/queries/query10.c
		gcc -c src/queries/query10.c -o obj/query10.o ${PKG_CONFIG}

main: obj/main.o obj/cat_commits.o obj/cat_repos.o obj/cat_users.o obj/command_interpreter.o obj/counter_hash.o obj/menus.o obj/parser.o obj/test_queries.o obj/query5.o obj/query6.o obj/query7.o obj/query8.o obj/query9.o obj/query9.o obj/query10.o
	$(CC) $(CCFLAGS) $(OBJ) -o guiao-3 -g ${PKG_CONFIG}
	$(CC) $(CCFLAGS) $(OBJ_TEST) -o tests -g ${PKG_CONFIG}
	doxygen Doxyfile

#Needed for debugging
## cc `pkg-config --cflags glib-2.0` hello.c -o hello `pkg-config --libs glib-2.0`

clean:
	rm -r guiao-3 tests obj/*.o docs/html docs/latex *.bin *.out bins/* *.csv testing/*.txt saida/*.txt saida/*.bin Query9Aux.txt Query10Aux.txt html latex
