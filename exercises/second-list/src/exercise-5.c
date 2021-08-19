/*
    This code was modified from the example 3.2 found in the textbook used in the course. 
    You can also find it in gpsilva2003 GitHub repository 
    (https://raw.githubusercontent.com/gpsilva2003/MPI/main/src/mpi_simples.c)

    What was modified for this exercise?
    1) etiq is now MPI_ANY_TAG in MPI_Recv
    2) origem is now MPI_ANY_SOURCE
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) { /* mpi_simples.c  */
int meu_ranque, num_procs;
int origem, destino, etiq;
origem = MPI_ANY_SOURCE;
etiq = 0;
char mensagem[200];
MPI_Status estado;
    /* Chamada inicial para o MPI */

    MPI_Init(&argc, &argv);
    /* Determina ranque e número de processos em execução */

    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Todos os processos com ranque diferente de 0 enviam uma mensagem */
    if (meu_ranque != 0) {
        sprintf(mensagem, "Processo %d está vivo!", meu_ranque);
        destino = 0;
        MPI_Send(mensagem, strlen(mensagem)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD);
    } 
    /* Processo com ranque 0 recebe num_procs-1 mensagens */
    else {
     
        // Expected output
        printf("Expected output:\n");
        for (int i = 1; i < num_procs; i++) {
            printf("Processo %d está vivo!\n",i);
        }

        printf("\nOutput:\n");
        for (int i = 1; i < num_procs; i++) {
            MPI_Recv(mensagem, 200, MPI_CHAR, origem, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
    /* Imprime as mensagens recebidas */
            printf("%s\n",mensagem); 
        }
    } 
    MPI_Finalize();
    return(0);
    
}