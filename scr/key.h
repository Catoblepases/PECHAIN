#ifndef INT64
#define INT64
// typedef long long int int64;
typedef long int64;
#endif

#ifndef __KEY
#define __KEY
typedef struct _Key {
    int64 val;
    int64 n;
} Key;

void  init_key(Key *key, int64 val, int64 n);
void  init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size);
char *key_to_str(Key *key);
Key  *str_to_key(char *str);
#endif