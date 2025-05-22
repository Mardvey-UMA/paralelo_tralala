// MPI_Dynamic_Message.cpp
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        // Генерация случайного размера сообщения (1-100 элементов)
        srand(time(NULL));
        int msg_size = rand() % 100 + 1;
        int* message = new int[msg_size];
        
        // Заполнение сообщения данными
        for(int i = 0; i < msg_size; i++) {
            message[i] = i;
        }
        
        // Отправка сообщения процессу 1
        MPI_Send(message, msg_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Процесс 0 отправил сообщение длины: " << msg_size << endl;
        
        delete[] message;
    } 
    else if (rank == 1) {
        // Получение информации о сообщении
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        
        // Определение размера сообщения
        int count;
        MPI_Get_count(&status, MPI_INT, &count);
        
        // Выделение памяти под сообщение
        int* received = new int[count];
        
        // Прием сообщения
        MPI_Recv(received, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        cout << "Процесс 1 получил сообщение длины: " << count << endl;
        cout << "Первые 3 элемента: ";
        for(int i = 0; i < min(3, count); i++) cout << received[i] << " ";
        cout << endl;
        
        delete[] received;
    }
    
    MPI_Finalize();
    return 0;
}