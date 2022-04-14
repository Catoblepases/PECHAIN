#include "prime.h"
#include "sgn.h"

#ifndef __PROTECTION__
#define __PROTECTION__

/**contient la cle publique de l'emetteur (l'electeur), son
message (sa declaration de vote), et la signature associee */
typedef struct _Protected {
    Key       *pKey;
    Signature *sgn;
    char      *mess;
} Protected;

Protected *init_protected(Key *pKey, char *mess, Signature *sgn);
int        verify(Protected *pr);
char      *protected_to_str(Protected *sgn);
Protected *str_to_protected(char *str);
void       generate_random_data(int nv, int nc);
void       free_protected(Protected *pr);
#endif