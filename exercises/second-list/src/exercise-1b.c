/*
    This code is the example 3.2 from the textbook used in the course. 
    You can also find it in gpsilva2003 GitHub repository 
    (https://raw.githubusercontent.com/gpsilva2003/MPI/main/src/mpi_simples.c)

    What was modified for this exercise?
    1) Now, we have two message arrays, one for the message to be sent and another to the message
    to be received. The latter has a very small dimension. 
    2) These arrays have different dimensions. The first has 200 elements while the latter has 100.
    3) The first argument of MPI_Send is now the mensagem_envio array and the first argument of MPI_Recv
    is now the mensagem_recepcao array.
    4) All the remaining references to mensagem array was updated to mensagem_envio, except that one after 
    MPI_Recv, which was updated to mensagem_recepcao.
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"


int main(int argc, char *argv[]) { /* mpi_simples.c  */
int meu_ranque, num_procs;
int origem, destino, etiq = 0;
char mensagem_envio[200];
char mensagem_recepcao[1];
MPI_Status estado;
    /* Chamada inicial para o MPI */

    MPI_Init(&argc, &argv);
    /* Determina ranque e número de processos em execução */

    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* Todos os processos com ranque diferente de 0 enviam uma mensagem */
    if (meu_ranque != 0) {
        sprintf(mensagem_envio, "Processo %d está vivo!", meu_ranque);
        destino = 0;
        MPI_Send(mensagem_envio, strlen(mensagem_envio)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD);
    } 
    /* Processo com ranque 0 recebe num_procs-1 mensagens */
    else {
        for (origem = 1; origem < num_procs; origem++) {
            MPI_Recv(mensagem_recepcao, 200, MPI_CHAR, origem, etiq, MPI_COMM_WORLD, &estado);
    /* Imprime as mensagens recebidas */
            printf("%s\n",mensagem_recepcao); 
        }
    } 
    MPI_Finalize();
    return(0);
}