/*
    This code was modified from the example 3.6 found in the textbook used in the course. 
    You can also find it in gpsilva2003 GitHub repository 
    (https://raw.githubusercontent.com/gpsilva2003/MPI/main/src/mpi_aleatorio.c)

    What was modified for this exercise?
    1) origem is now MPI_ANY_SOURCE
    2) destino is now 0
    3) added a variable to store the number of processes
    4) all processes, except that one with rank equals to 0, is now sending a message
    5) srand was modified to (meu_ranque+meu_ranque*meu_ranque)
*/

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MAX 100

int main(int argc, char *argv[]) { /* mpi_aleatorio.c  */
    int meu_ranque, total_num, etiq = 0;
    int origem=MPI_ANY_SOURCE, destino=0, numeros[MAX], num_procs;
    MPI_Status estado;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    if (meu_ranque != destino) {
    /* Escolhe uma quantidade aleatória de inteiros para enviar para o processo 0 */
        srand(meu_ranque+meu_ranque*meu_ranque);
        total_num = (rand() / (float)RAND_MAX) * MAX;
    /* Envia a quantidade de inteiros para o processo 1 */
        
        // Synchronous send
        //MPI_Ssend(numeros, total_num, MPI_INT, destino, etiq, MPI_COMM_WORLD);

        // Default send
        MPI_Send(numeros, total_num, MPI_INT, destino, etiq, MPI_COMM_WORLD);
        
        printf("Processo %d enviou %d números para 1\n", meu_ranque, total_num);
    } 
    else {
        /* Recebe no máximo MAX números do processo 0 */
        MPI_Recv(numeros, MAX, MPI_INT, origem, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
        /* Quando chega a mensagem, verifica o status para determinar quantos números foram realmente recebidos */
        MPI_Get_count(&estado, MPI_INT, &total_num);
        /* Imprime a quantidade de números e a informação
        adicional que está no manipulador "estado" */
        printf("Processo %d recebeu %d números. Origem da mensagem = %d, etiqueta = %d\n", destino, total_num, estado.MPI_SOURCE, estado.MPI_TAG);
    }
    MPI_Finalize();           
    return(0);
}