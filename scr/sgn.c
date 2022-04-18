#include "sgn.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**alloue et initialise structure Signature*/
Signature *init_signature(long *content, int size) {
    Signature *sgn = (Signature *) malloc(sizeof(Signature));
    if (!sgn) exit(3);
    sgn->content = content;
    sgn->size = size;
    return sgn;
}

/**Encoder le message selon la clé secrète et générer une signature*/
Signature *sign(char *mess, Key *sKey) {
    long *ency = encrypt(mess, sKey->val, sKey->n);
    return init_signature(ency, strlen(mess));
}

/**permettent de passer d’un Signature a sa representation sous forme de chaıne de caracteres.*/
char *signature_to_str(Signature *sgn) {
    char *result = malloc(10 * sgn->size * sizeof(char));
    if (!result) exit(3);
    result[0] = '#';
    int pos = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++) {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j = 0; j < strlen(buffer); j++) {
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos + 1;
    }
    result[pos] = '\0';
    result = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

/**permettent de passer d’un chaıne de caracteres a structure Signature*/
Signature *str_to_signature(char *str) {
    int len = strlen(str);
    long *content = (long *) malloc(sizeof(long) * len);
    if (!content) exit(3);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != '#') {
            buffer[pos] = str[i];
            pos = pos + 1;
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

/**Liberer l'espace occupé par signature*/
void free_signature(Signature *sgn) {
    if (sgn) {
        free(sgn->content);
        free(sgn);
    }
}