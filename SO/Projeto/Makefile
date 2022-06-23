all: client server #server client 

server: bin/sdstored

client: bin/sdstore

bin/sdstored: obj/sdstored.o obj/logger.o obj/parser.o obj/pipe.o obj/request.o obj/transformations.o obj/queue.o obj/scheduler.o
	gcc -g obj/sdstored.o obj/logger.o obj/parser.o obj/pipe.o obj/request.o obj/transformations.o obj/queue.o obj/scheduler.o -o bin/sdstored

obj/sdstored.o: src/sdstored.c
	gcc -Wall -g -c src/sdstored.c -o obj/sdstored.o

bin/sdstore: obj/sdstore.o obj/logger.o obj/parser.o obj/pipe.o obj/request.o
	gcc -g obj/sdstore.o obj/logger.o obj/parser.o obj/pipe.o obj/request.o -o bin/sdstore

obj/sdstore.o: src/sdstore.c
	gcc -Wall -g -c src/sdstore.c -o obj/sdstore.o

obj/logger.o: src/common/logger.c
	gcc -Wall -g -c src/common/logger.c -o obj/logger.o

obj/parser.o: src/common/parser.c
	gcc -Wall -g -c src/common/parser.c -o obj/parser.o

obj/pipe.o: src/common/pipe.c
	gcc -Wall -g -c src/common/pipe.c -o obj/pipe.o

obj/request.o: src/common/request.c
	gcc -Wall -g -c src/common/request.c -o obj/request.o

obj/transformations.o: src/common/transformations.c
	gcc -Wall -g -c src/common/transformations.c -o obj/transformations.o

obj/queue.o: src/server/queue.c
	gcc -Wall -g -c src/server/queue.c -o obj/queue.o

obj/scheduler.o: src/server/scheduler.c
	gcc -Wall -g -c src/server/scheduler.c -o obj/scheduler.o

clean: 
	rm bin/sdstore bin/sdstored obj/* tmp/*
	

