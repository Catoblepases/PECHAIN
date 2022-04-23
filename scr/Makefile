CFLAGS= -g -Wall

OBJECTS = prime rsa sgn pro key lck lcp hash blo blo_t sml

all: $(OBJECTS:=.o)

clean:
	rm -f *.o
	rm -f $(OBJECTS:=)
	
cleanAll:
	rm -f *.o
	rm -f $(OBJECTS:=)
    rm -f *.txt
	rm -f *.csv
	

$(OBJECTS:=.o):%.o: %.c %.h
	$(CC) $(CFLAGS) -c $(word 1,$^)