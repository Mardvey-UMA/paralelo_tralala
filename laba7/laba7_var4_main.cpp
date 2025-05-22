// MPI_Send_Recv_Timer.cpp
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    const int NTimes = 100;
    char Proc_Name[MPI_MAX_PROCESSOR_NAME + 1];
    int rank, size;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size % 2 != 0) {
        if (rank == 0) {
            cerr << "This program requires an even number of processes." << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    int NLen;
    MPI_Get_processor_name(Proc_Name, &NLen);
    double tick = MPI_Wtick();
    
    int partner_rank = (rank % 2 == 0) ? rank + 1 : rank - 1;
    int dummy = 0;
    double time_start = MPI_Wtime();
    
    for (int i = 0; i < NTimes; ++i) {
        if (rank % 2 == 0) {
            MPI_Send(&dummy, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            MPI_Recv(&dummy, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(&dummy, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&dummy, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
        }
    }
    
    double time_finish = MPI_Wtime();
    double avg_time = (time_finish - time_start) / NTimes;
    
    cout << "Processor " << rank << " " << Proc_Name << endl
         << "timer's tick=" << tick << " time=" << avg_time << endl;
    
    MPI_Finalize();
    return 0;
}