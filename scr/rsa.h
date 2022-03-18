#ifndef __RSA
#define __RSA
#include "libp.h"
int64  extended_gcd(int64 s, int64 t, int64 *u, int64 *v);
void   generate_key_values(int64 p, int64 q, int64 *n, int64 *s, int64 *u);
int64 *encrypt(char *chaine, int64 s, int64 n);
char * decrypt(int64 *crypted, int size, int64 u, int64 n);
void   print_long_vector(int64 *result, int size);
#endif