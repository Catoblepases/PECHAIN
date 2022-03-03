all : run clean

run: main
	./main

main : main.o biblioH.o entreeSortieH.o
	gcc -ggdb -Wall -g -o main main.o biblioH.o entreeSortieH.o 

main.o : main.c entreeSortieH.h biblioH.h
	gcc -Wall -g -c main.c

biblioH.o : biblioH.c biblioH.h 
	gcc -Wall -g -c biblioH.c

entreeSortieH.o : entreeSortieH.c entreeSortieH.h
	gcc -Wall -g -c entreeSortieH.c

clean :
	rm -f *.o main