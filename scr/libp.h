#ifndef INT64
#define INT64
// typedef long long int int64;
typedef long int64;
#endif

#ifndef __LIBP
#define __LIBP

int   is_prime_naive(int64 p);
int64 modpow_naive(int64 a, int64 m, int64 n);
int64 modpow(int64 a, int64 m, int64 n);
int   witness(int64 a, int64 b, int64 d, int64 p);
int64 rand_long(int64 low, int64 up);
int   is_prime_miller(int64 p, int k);
int64 random_prime_number(int low_size, int up_size, int k);

#endif
