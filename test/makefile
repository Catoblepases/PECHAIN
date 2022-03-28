CFLAGS=-Wall
EXE_OUTPUT=$(D_ROOT)/build/tests
TEST_FILES = rsa pro libp sgn key lck lcp

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

clean :
	rm -f *.o
	rm -f *.exe

$(TEST_FILES): %: $(D_LIB)/%.o %.c
	$(CC) $(CFLAGS) -o $@ $@.c $(TEST_FILES:%=$(D_LIB)/%.o)