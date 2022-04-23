#!/bin/bash
# Fichier "vote-nir"
sed -i 's/\r$//' runn.sh
clear
echo "--------run-test----------";
make clean;
make;
make test;

# cd test;
# valgrind -s  --leak-check=full --track-origins=yes --log-file=test_valgrind.log --num-callers=30 ./sml;