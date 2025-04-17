#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    const int NTimes = 100;
    const int Master = 0;
    const int Tag = 0;
    char Proc_Name[MPI_MAX_PROCESSOR_NAME+1];
    int message = 0;
    int reply = 0;
    
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int NLen;
    MPI_Get_processor_name(Proc_Name, &NLen);
    
    double tick = MPI_Wtick();
    double time_start = MPI_Wtime();
    
    for (int i = 1; i <= NTimes; i++) {
        if (rank == Master) {
            // Мастер отправляет сообщение следующему процессу
            int dest = (rank + 1) % size;
            MPI_Send(&message, 1, MPI_INT, dest, Tag, MPI_COMM_WORLD);
            
            // Ожидание ответа
            MPI_Recv(&reply, 1, MPI_INT, dest, Tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            // Ожидание сообщения
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, Tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            // Отправка ответа
            int dest = (rank - 1 + size) % size;
            MPI_Send(&reply, 1, MPI_INT, dest, Tag, MPI_COMM_WORLD);
        }
    }
    
    double time_finish = MPI_Wtime();
    
    cout << "Processor " << rank << " " << Proc_Name << endl
         << "timer's tick=" << tick << " average time="
         << (time_finish - time_start)/NTimes << endl;
    
    MPI_Finalize();
    return 0;
}