#ifndef __SGN
#define __SGN

#include "key.h"

typedef struct signature {
    int   size;
    long *content;
} Signature;

Signature *init_signature(long *content, int size);
Signature *sign(char *mess, Key *sKey);
char      *signature_to_str(Signature *sgn);
char *signature_to_str_static(Signature *sgn);
Signature *str_to_signature(char *str);
void       free_signature(Signature *sgn);

#endif