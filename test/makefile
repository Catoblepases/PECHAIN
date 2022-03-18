CFLAGS=-Wall
EXE_OUTPUT=$(D_ROOT)/build/tests
TEST_FILES = rsa pro

all:

run: $(TEST_FILES)
	for ftest in $(TEST_FILES); do \
		echo  ;\
		echo ==============================================; \
		echo :: running "$$ftest" tests; \
		echo ==============================================; \
		echo  ;\
		./$$ftest; \
	done
	echo $(TEST_FILES:%=$(D_LIB)/%.o)

clean :
	rm -f *.o main

$(TEST_FILES): %: $(D_LIB)/%.o %.c
	$(CC) $(CFLAGS) -o $@ $@.c $(TEST_FILES:%=$(D_LIB)/%.o) $(D_LIB)/libp.o