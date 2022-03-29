#include "sgn.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Signature *init_signature(long *content, int size) {
    Signature *sgn = (Signature *) malloc(sizeof(Signature));
    sgn->content   = content;
    sgn->size      = size;
    return sgn;
}

Signature *sign(char *mess, Key *sKey) {
    long *ency = encrypt(mess, sKey->val, sKey->n);
    return init_signature(ency, strlen(mess));
}

char *signature_to_str(Signature *sgn) {
    char *result = malloc(10 * sgn->size * sizeof(char));
    result[0]    = '#';
    int  pos     = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++) {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j = 0; j < strlen(buffer); j++) {
            result[pos] = buffer[j];
            pos         = pos + 1;
        }
        result[pos] = '#';
        pos         = pos + 1;
    }
    result[pos] = '\0';
    result      = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

Signature *str_to_signature(char *str) {
    int   len     = strlen(str);
    long *content = (long *) malloc(sizeof(long) * len);
    int   num     = 0;
    char  buffer[256];
    int   pos = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != '#') {
            buffer[pos] = str[i];
            pos         = pos + 1;
        } else {
            if (pos != 0) {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content, num * sizeof(long));
    return init_signature(content, num);
}

void free_signature(Signature *sgn) {
    free(sgn->content);
    free(sgn);
}