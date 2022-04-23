CFLAGS=-g -Wall
TEST_FILES = rsa pro prime sgn key lck lcp hash blo blo_t sml

all:


run: $(TEST_FILES)
	for test in $(TEST_FILES); do \
		echo  ;\
		echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
		echo test: "$$test"; \
		echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
		echo  ;\
		./$$test; \
	done

clean :
	rm -f *.o
	rm -f *.exe
	rm -f $(TEST_FILES)
	rm -f ./blockchain/*.txt

cleanAll:
	rm -f *.o *.exe *.txt *.csv *.log
	rm -f $(TEST_FILES)
	rm -f ./temp/*.txt
	rm -f ./blockchain/*.txt

$(TEST_FILES): %: $(D_LIB)/%.o %.c
	$(CC) $(CFLAGS) -o $@ $@.c $(TEST_FILES:%=$(D_LIB)/%.o) -lssl -lcrypto