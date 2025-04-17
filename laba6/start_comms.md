```bash
# Последовательная версия
g++ Matr_Mult.cpp -o seq_mat_mult -O0

# Параллельная версия
g++ Matr_Mult.cpp -o par_mat_mult -O3 -fopenmp

./seq_mat_mult
./par_mat_mult
```

```bash
# однопоточный BLAS
OPENBLAS_NUM_THREADS=1 g++ Matr_Mult_BLAS.cpp -o seq_blas_mult -O3 -lopenblas

# Параллельная версия
g++ Matr_Mult_BLAS.cpp -o par_blas_mult -O3 -lopenblas

```

```bash

# однопоточный LAPACK
OPENBLAS_NUM_THREADS=1 g++ Lin_Solv_LAPACK.cpp -o seq_lapack_solve -O3 -lopenblas


# многопоточный LAPACK
g++ Lin_Solv_LAPACK.cpp -o par_lapack_solve -O3 -lopenblas
```
