//MPI_BCAST_GATHER.cpp
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{double a=0;
MPI_Init(NULL,NULL);
int Size;
MPI_Comm_size(MPI_COMM_WORLD, &Size);
int Rank;
MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
if (Rank == 0)
a = 0.3;
//"Широковещательная" рассылка сообщения
MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
if (Rank==0){
double *A=new double[Size];
MPI_Gather(&a, 1, MPI_DOUBLE, A, 1, MPI_DOUBLE, 0,
MPI_COMM_WORLD);
for (int k=0; k<Size; k++)
cout<<A[k]<<endl;
delete[] A;
}
else{
double b=a+Rank;
MPI_Gather(&b, 1, MPI_DOUBLE, NULL, 0, MPI_DOUBLE, 0,
MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}