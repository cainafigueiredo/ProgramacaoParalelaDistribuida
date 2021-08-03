# Compiling the codes

## Sequential Version
*gcc src/sequential.c -o bin/sequential -lm*

## Paralel Version
*mpicc src/paralel.c -o bin/paralel -lm*

# Executing the codes

## Sequential Version
*./bin/sequential*

## Paralel Version
*mpirun -n <Number of processes> ./bin/paralel*
