# Compiling the codes

## Sequential Version
*gcc src/sequential.c -o bin/sequential -lm*

## Paralel Version
*mpicc src/paralel.c -o bin/paralel -lm*

# Executing the experiments
*./run-experiments* (It will create a number of files in './data')

# Analysing the experiments
You can generate a speedup curve for your experiments with the jupyter notebook at 'analyis' directory.
