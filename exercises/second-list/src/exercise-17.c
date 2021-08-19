#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int meu_ranque, num_procs, vetor[10], vetor1[3], vetor2[3], vetor3[4], position = 0;
    MPI_Status estado;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (num_procs < 4) {
        printf("This program requires more than 4 processes. Please, try to execute it again.\n");
        MPI_Finalize();
        exit(0);
    }

    if (meu_ranque == (num_procs - 1)) {
        // Initializing vetor
        for (int i = 0; i < 10; i++) {
            vetor[i] = i+1;
        }

        // Packing and sending values
        MPI_Send(&vetor[0], 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&vetor[3], 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&vetor[6], 4, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    else if (meu_ranque == 0) {
        MPI_Recv(&vetor1, 3, MPI_INT, (num_procs - 1), 0, MPI_COMM_WORLD, &estado);
        printf("Process %d received the values: %d, %d, %d\n", meu_ranque, vetor1[0], vetor1[1], vetor1[2]);
    }

    else if (meu_ranque == 1) {
        MPI_Recv(&vetor2, 3, MPI_INT, (num_procs - 1), 0, MPI_COMM_WORLD, &estado);
        printf("Process %d received the values: %d, %d, %d\n", meu_ranque, vetor2[0], vetor2[1], vetor2[2]);
    }

    else if (meu_ranque == 2) {
        MPI_Recv(&vetor3, 4, MPI_INT, (num_procs - 1), 0, MPI_COMM_WORLD, &estado);
        printf("Process %d received the values: %d, %d, %d, %d\n", meu_ranque, vetor3[0], vetor3[1], vetor3[2], vetor3[3]);
    }

    MPI_Finalize();

    return 0;
}