CFLAGS= -g -Wall

OBJECTS = libp rsa sgn pro key lck lcp dge

all: $(OBJECTS:=.o)

clean:
	rm -f $(OBJECTS:=.o)
	rm -f $(OBJECTS:=)
	

$(OBJECTS:=.o):%.o: %.c %.h
	$(CC) $(CFLAGS) -c $(word 1,$^)