CFLAGS=-g -Wall
TEST_FILES = rsa pro libp sgn key lck lcp

all:

run: $(TEST_FILES)
	for test in $(TEST_FILES); do \
		echo  ;\
		echo ------------------------------------------------; \
		echo test: "$$test"; \
		echo ------------------------------------------------; \
		echo  ;\
		./$$test; \
	done

clean :
	rm -f *.o
	rm -f *.exe

$(TEST_FILES): %: $(D_LIB)/%.o %.c
	$(CC) $(CFLAGS) -o $@ $@.c $(TEST_FILES:%=$(D_LIB)/%.o)