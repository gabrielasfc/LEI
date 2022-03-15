CC = gcc

CFLAGS = -Wall

all: mycat mycp myreadln mynl

mycat : mycat.o

mycat.o : mycat.c

mycp : mycp.o

mycp.o : mycp.c

myreadln : myreadln.o

myreadln.o : myreadln.c

mynl : mynl.o

mynl.o : mynl.c

clean: 
	@rm mycat mycp myreadln mynl
	@rm *.o
	@rm -rf *.dSYM