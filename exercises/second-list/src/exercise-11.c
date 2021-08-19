#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>

#define MSG_STRING "This is my message. You can try to change it."

int main(int argc, char *argv[]) {

    char *mensagem_envio = MSG_STRING;
    char *mensagem_recepcao;
    int meu_ranque, total_char, num_procs, origem, destino = 0;
    MPI_Status estado;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    origem = (num_procs-1);

    // Only the process with the higher will send the message, since this doesn't matter for this exercise
    if (meu_ranque == origem) {
        MPI_Send(mensagem_envio, strlen(mensagem_envio)+1, MPI_CHAR, destino, 0, MPI_COMM_WORLD);
    } 

    else if (meu_ranque == destino) {
        MPI_Probe(origem, 0, MPI_COMM_WORLD, &estado);
        
        // Alocating mensagem_recepcao
        MPI_Get_count(&estado, MPI_CHAR, &total_char);
        mensagem_recepcao = (char*) calloc(total_char, sizeof(char));
        
        MPI_Recv(mensagem_recepcao, total_char, MPI_CHAR, origem, 0, MPI_COMM_WORLD, &estado);
        printf("The process 0 received the following message with %d elements:\n%s\n", total_char, mensagem_recepcao);

        free(mensagem_recepcao);
    }

    MPI_Finalize();

    return 0;
}