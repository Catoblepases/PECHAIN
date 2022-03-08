#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500
#define A 1300

int main(int argc, char const *argv[]) {
    /*long num = 1;
    int  a   = 4;
    for (int i = 0; i < 19; i++) {
        num = num * a;
    }
    printf("%ld,%ld", num, num % 86);*/

    FILE *fic=fopen("sortie_vitesse.txt","w");
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;


    for(long long i=100000000000;i<100000000003;i++){
        fprintf(fic,"%I64d ",i);

        temps_initial=clock();
        modpow_naive(A, i,N );
        temps_final=clock();
        temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
        fprintf(fic,"%.10f ",temps_cpu);

        temps_initial=clock();
        modpow(A, i,N);
        temps_final=clock();
        temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
        fprintf(fic,"%.10f\n",temps_cpu);
    }
    fclose(fic);

    
    return 0;
}
