#ifndef __KEY__
#define __KEY__

/* une structure Key qui contient deux long représentant une clé (publique ou secrète).*/
typedef struct _Key {
    long val;
    long n;
} Key;

void init_key(Key *key, long val, long n);
void init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size);
char *key_to_str(Key *key);
Key *str_to_key(char *str);
char *key_to_str_static(Key *key);
Key *str_to_key_static(char *str);
int compare_key(Key *key1, Key *key2);
#endif