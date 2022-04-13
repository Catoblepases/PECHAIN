#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    // char *s  = "hellksalklakdlkklkl;ak;ldal;kd;lo";
    // char *in = malloc(256 * sizeof(char));
    // strcpy(in, s);
    // printf("%s ", in);
    // strcat(in, s);
    // printf("%s", in);

    char *tmp[3];
    int   i = 0;

    char  str[] = "(2573,3937) (737,179) #c6c#259#ad1#259#b2f#b95#259#35f#34e#";
    char *st    = strtok(str, " ");
    while (st != NULL) {
        printf("%s\n", st);
        // free(st);
        tmp[i++] = st;
        st       = strtok(NULL, " ");
    }

    // char *tmp[3];
    // int   separate = 1;
    // int   begin, pointAt = 0;
    // for (int idx = 0; idx < strlen(str); idx++) {
    //     if (separate) {
    //         begin    = idx;
    //         separate = 0;
    //     } else if ((str[idx] == ' ') || (idx == strlen(str) - 1)) {
    //         separate     = 1;
    //         tmp[pointAt] = malloc(sizeof(char) * (idx - begin + 2));
    //         if (idx == strlen(str) - 1) {
    //             strncpy(tmp[pointAt], str + begin, idx - begin + 1);
    //         } else {
    //             strncpy(tmp[pointAt], str + begin, idx - begin);
    //         }
    //         printf("\n%d: %s(%ld)\n", idx, tmp[pointAt], strlen(tmp[pointAt]));
    //         pointAt++;
    //     }
    // }
    for (int i = 0; i < 3; i++) {
        if (!tmp[i]) {
            printf("warnning!");
            exit(EXIT_FAILURE);
        }
    }

    // Key       *key = str_to_key(tmp[0]);
    // Signature *sgn = str_to_signature(tmp[1]);
    // Protected *pr  = init_protected(key, tmp[2], sgn);
    printf("result: %s %s %s\n", tmp[0], tmp[1], tmp[2]);
    // for (int i = 0; i < 3; i++) {
    //     free(tmp[i]);
    // }
    return 0;
}
