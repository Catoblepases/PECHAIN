CFLAGS= -g -Wall

OBJECTS = prime rsa sgn pro key lck lcp hash blo blo_t sml

all: $(OBJECTS:=.o)

clean:
	rm -f $(OBJECTS:=.o)
	rm -f $(OBJECTS:=)
	

$(OBJECTS:=.o):%.o: %.c %.h
	$(CC) $(CFLAGS) -c $(word 1,$^)