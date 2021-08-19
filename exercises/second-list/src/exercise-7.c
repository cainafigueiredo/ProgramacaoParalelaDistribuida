/*
    This code was modified from the example 3.12 found in the textbook used in the course. 
    You can also find it in gpsilva2003 GitHub repository 
    (https://raw.githubusercontent.com/gpsilva2003/MPI/main/src/mpi_bcast.c)

    What was modified for this exercise?
    1) "valor" is now an int 5-dimensional array
    2) MPI_Bcast was modified to send 5 elements of "valor"
    3) The program is now printing all the values of the array
    4) The values filling is now made through memset function

*/

#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[]) { /* mpi_bcast.c  */
    int valor[5];
    int meu_ranque, raiz = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    /* Cada processo tem um valor inicial diferente */
    memset(valor, meu_ranque, 5*sizeof(int));
    /* O valor a ser enviado é lido pelo processo raiz */
    if (meu_ranque == raiz) {
        for (int i = 0; i < 5; i++) {
            printf("Entre um valor: \n");
            scanf("%d", &valor[i]);    
        }
    }
    /* A rotina de difusão é chamada por todos processos, apenas o processo raiz envia, os demais recebem */
    MPI_Bcast(&valor, 5, MPI_INT, raiz, MPI_COMM_WORLD);
    /* O valor agora é o mesmo em todos os processos */
    printf("O processo com ranque %d recebeu os valores: %d, %d, %d, %d, %d\n",meu_ranque, valor[0], valor[1], valor[2], valor[3], valor[4]);
    
    /* Termina a execução */
    MPI_Finalize();
    return 0;
}