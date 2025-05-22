// MPI_Timer_Info_RU.cpp
#include "mpi.h"
#include <iostream>
#include <locale.h>
using namespace std;

int main(int argc, char **argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установка русской локали
    
    const int NTimes = 100000;
    char Proc_Name[MPI_MAX_PROCESSOR_NAME + 1];
    
    MPI_Init(NULL, NULL);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int name_len;
    MPI_Get_processor_name(Proc_Name, &name_len);
    
    double tick = MPI_Wtick();
    double total_time = 0.0;

    for (int i = 0; i < NTimes; ++i) {
        double start = MPI_Wtime();
        double end = MPI_Wtime();
        total_time += (end - start);
    }
    
    double avg_time = total_time / NTimes;
    
    cout << "Процесс " << rank << ":" << endl
         << "1. Имя узла: " << Proc_Name << endl
         << "2. Разрешение таймера: " << tick << " сек" << endl
         << "3. Среднее время замера: " << avg_time << " сек" << endl
         << endl;
    
    MPI_Finalize();
    return 0;
}