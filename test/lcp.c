#include "scr/lcp.h"
#include "scr/pro.h"
#include "scr/utility.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
    print_with_sepatator("read_protected");
    CellProtected *LCP = read_protected(FILE_DECLARATIONS);
    print_with_sepatator("print_list_protected");
    print_list_protected(LCP);
    print_with_sepatator("verify_for_list_protected");
    printf("number of error signatures: %d\n", verify_for_list_protected(&LCP));
    print_with_sepatator("delete_list_protected");
    delete_list_protected(LCP);
    return 0;
}