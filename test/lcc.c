#include "scr/lcc.h"
#include "scr/key.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) { 
    print_list_keys(read_public_keys("key.txt"));

    return 0;
}