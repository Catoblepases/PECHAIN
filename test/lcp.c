#include "scr/lcp.h"
#include "scr/pro.h"
#include <stdio.h>
#include <stdlib.h>
#define FILENAME "declarations.txt"
int main(int argc, char const *argv[]) {
    CellProtected *LCP = read_protected(FILENAME);
    print_list_protected(LCP);
    delete_list_protected(LCP);
    return 0;
}