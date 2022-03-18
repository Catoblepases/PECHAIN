#ifndef __SGN
#define __SGN

#include "key.h"

typedef long long int int64;
typedef struct signature {
    int    size;
    int64 *content;
} Signature;

Signature *init_signature(int64 *content, int size);
Signature *sign(char *mess, Key *sKey);
char *     signature_to_str(Signature *sgn);
Signature *str_to_signature(char *str);

#endif