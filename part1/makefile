all : run

run :test
	./test
test : test.o libp.o 
	gcc -ggdb -Wall -g -o test test.o libp.o 

test.o : test.c libp.h 
	gcc -Wall -g -c test.c

libp.o : libp.c libp.h 
	gcc -Wall -g -c libp.c

clean :
	rm-f *.o
	rm-f test