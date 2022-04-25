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

ex1: prime
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "prime"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./prime; \

ex2: prime rsa
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "rsa"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./rsa; \

ex3: prime rsa key sgn pro
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "pro"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./pro; \

ex4: prime rsa key sgn pro 
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "pro"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./pro; \

ex5: prime rsa key sgn pro lck lcp
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "lck"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./lck; \
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "lcp"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./lcp; \

ex6: prime rsa key sgn pro lck lcp hash
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "hash"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./hash; \

ex7: prime rsa key sgn pro lck lcp hash blo
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "blo"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./blo; \

ex8: prime rsa key sgn pro lck lcp hash blo blo_t
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "blo_t"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./blo_t; \

ex9: prime rsa key sgn pro lck lcp hash blo blo_t sml
	echo  ;\
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo test: "sml"; \
	echo ++++++++++++++++++++++++++++++++++++++++++++++++; \
	echo  ;\
	./sml; \

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