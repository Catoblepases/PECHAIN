rm test;
gcc -g -Wall -o test test.c;
valgrind -s  --leak-check=full --track-origins=yes --log-file=test_valgrind.log --num-callers=30 ./hash;