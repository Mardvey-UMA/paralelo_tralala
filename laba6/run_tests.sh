#!/bin/bash

# Очистка старых данных
echo "Method,Version,Time(ms)" > results.csv

# Наивное умножение
echo "Testing naive matrix multiplication..."
for i in {1..3}; do
    echo "Naive,Sequential,$(./seq_mat_mult | grep -oP 'Time=\K\d+')" >> results.csv
    echo "Naive,Parallel,$(./par_mat_mult | grep -oP 'Time=\K\d+')" >> results.csv
done

# BLAS умножение
echo "Testing BLAS matrix multiplication..."
for i in {1..3}; do
    echo "BLAS,Sequential,$(OPENBLAS_NUM_THREADS=1 ./par_blas_mult | grep -oP 'Time=\K\d+')" >> results.csv
    echo "BLAS,Parallel,$(./par_blas_mult | grep -oP 'Time=\K\d+')" >> results.csv
done

# LAPACK решение СЛАУ
echo "Testing LAPACK linear solver..."
for i in {1..3}; do
    echo "LAPACK,Sequential,$(OPENBLAS_NUM_THREADS=1 ./par_lapack_solve | grep -oP 'Time=\K\d+')" >> results.csv
    echo "LAPACK,Parallel,$(./par_lapack_solve | grep -oP 'Time=\K\d+')" >> results.csv
done

echo "Results saved to results.csv"
