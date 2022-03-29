

#ifndef __KEY__
#define __KEY__
typedef struct _Key {
    long val;
    long n;
} Key;

void  init_key(Key *key, long val, long n);
void  init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size);
char *key_to_str(Key *key);
Key  *str_to_key(char *str);
#endif