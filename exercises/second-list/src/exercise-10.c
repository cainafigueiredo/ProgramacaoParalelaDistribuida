#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int token, meu_ranque, num_procs, origem, destino;
    MPI_Status estado;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (meu_ranque == 0) {

        // Asking to user input an init value for the token.
        printf("Init token with value: \n");

        scanf("%d", &token);

        // Start communication
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 started the communication with token equals to %d.\n", token);

    }
    
    do {
        origem = (meu_ranque-1);
        if (origem < 0) {
            origem = num_procs-1;
        }
        MPI_Recv(&token, 1, MPI_INT, origem, 0, MPI_COMM_WORLD, &estado);
        printf("Process %d received the token from process %d with value %d.\n", meu_ranque, origem, token);

        if (meu_ranque == 0) {
            token--;
            printf("Process 0 decremented token.\n");
        }

        destino = (meu_ranque+1)%num_procs;
        MPI_Send(&token, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        printf("Process %d sent the token to process %d with value %d.\n", meu_ranque, destino, token);
    } while(token);

    MPI_Finalize();

    return 0;
}