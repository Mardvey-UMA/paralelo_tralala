#include "mpi.h"
#include <iostream>
using namespace std;

const int N = 8;

// Пользовательская функция для операции сложения по модулю 8
void UsrFunc(void *In, void *InOut, int *len, MPI_Datatype *Ty) {
    int *InV = (int *)In;
    int *InOutV = (int *)InOut;
    for (int k = 0; k < (*len); k++) {
        InOutV[k] = (InV[k] + InOutV[k]) % 8;
    }
}

int main(int argc, char **argv) {
    int *A = new int[N];
    MPI_Init(&argc, &argv);
    
    int Rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    
    for (int k = 0; k < N; k++) {
        A[k] = k + Rank;
    }

    MPI_Op My_Op;
    MPI_Op_create(UsrFunc, 1, &My_Op); 
    
    if (Rank == 0) {
        int *B = new int[N];
        
        MPI_Reduce(A, B, N, MPI_INT, My_Op, 0, MPI_COMM_WORLD);
        
        for (int k = 0; k < N; k++) {
            cout << B[k] << " ";
        }
        cout << endl;
        
        delete[] B;
    } else {
        MPI_Reduce(A, NULL, N, MPI_INT, My_Op, 0, MPI_COMM_WORLD);
    }
    
    MPI_Op_free(&My_Op);
    delete[] A;
    MPI_Finalize();
    return 0;
}
//
// Process 0: [0,1,2,3,4,5,6,7]
// Process 1: [1,2,3,4,5,6,7,8]
// Process 2: [2,3,4,5,6,7,8,9]
// Process 3: [3,4,5,6,7,8,9,10]