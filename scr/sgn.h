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
Signature *str_to_signature(char *str);

#endif