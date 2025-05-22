// MPI_Ring_Topology_RU.cpp
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <locale.h>

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            cerr << "Требуется минимум 2 процесса!" << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Определение соседей в кольце
    int prev_rank = (rank - 1 + size) % size;
    int next_rank = (rank + 1) % size;

    // Выделение буфера для буферизованной отправки
    int* buffer;
    int buffer_size = sizeof(int) + MPI_BSEND_OVERHEAD;
    buffer = (int*)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    // Подготовка данных для отправки
    int send_data = rank * 10;
    MPI_Request request;

    // Неблокирующая буферизованная отправка следующему процессу
    MPI_Ibsend(&send_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD, &request);

    // Блокирующий прием от предыдущего процесса
    int recv_data;
    MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Ожидание завершения операции отправки
    MPI_Wait(&request, MPI_STATUS_IGNORE);

    // Освобождение буфера
    MPI_Buffer_detach(buffer, &buffer_size);
    free(buffer);

    // Вывод результатов
    cout << "Процесс " << rank 
         << " отправил данные: " << send_data 
         << " процессу " << next_rank 
         << ", получил: " << recv_data 
         << " от процесса " << prev_rank << endl;

    MPI_Finalize();
    return 0;
}
