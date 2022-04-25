!/bin/bash
# clear;
# make clean;
# make;
# make test;

cd test;
valgrind -s  --leak-check=full --track-origins=yes --log-file=test_valgrind.log --num-callers=30 ./sml;
cd ..;