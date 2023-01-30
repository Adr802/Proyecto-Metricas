#include <stdio.h>
#include <libreria.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
int main()
{
    int v1[500];
    int v2[500];
    double iniciar, finalizar;
    iniciar = omp_get_wtime();
    srand (time(NULL));
    for(int i=0; i<500; i++){
        v1[i] = rand() % 2;
        v2[i] = rand() % 2;
    }

    for(int i=0; i<500; i++){
        printf("[1] %d\n", v1[i]);
        printf("[2] %d\n\n", v2[i]);
    }

    printf("El BER es: %f", BER(v1,v2));
    printf("\nEl BCR es: %f\n", BCR(v1,v2));
    printf("Suma: %f\n", (BER(v1,v2) + BCR(v1,v2)));
    CorrectDetectionRate(v1, v2);
    finalizar = omp_get_wtime();
    printf("El tiempo de la multiplicacion es: %f segundos\n", finalizar - iniciar);

    return 0;
}



