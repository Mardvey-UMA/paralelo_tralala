// MPI_Master_Slave_RU.cpp
#include <mpi.h>
#include <iostream>
#include <vector>
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
            cerr << "Для работы программы требуется минимум 2 процесса!" << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) { // Ведущий процесс
        vector<MPI_Request> requests(size-1);
        vector<MPI_Status> statuses(size-1);
        vector<int> data(size-1);
        vector<int> indices(size-1);
        int outcount;
        
        // Инициализация неблокирующего приема
        for (int i = 1; i < size; ++i) {
            MPI_Irecv(&data[i-1], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &requests[i-1]);
        }
        
        // Ожидание завершения операций
        cout << "Главный процесс начал ожидание сообщений..." << endl;
        MPI_Waitsome(size-1, requests.data(), &outcount, indices.data(), statuses.data());
        
        // Обработка полученных данных
        for (int i = 0; i < outcount; ++i) {
            int idx = indices[i];
            cout << "Получено сообщение от процесса " << (idx+1) 
                 << " с данными: " << data[idx] << endl;
        }
    } 
    else { // Ведомые процессы
        int data_to_send = rank * 10;
        MPI_Send(&data_to_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        cout << "Процесс " << rank << " отправил данные: " << data_to_send << endl;
    }
    
    MPI_Finalize();
    return 0;
}