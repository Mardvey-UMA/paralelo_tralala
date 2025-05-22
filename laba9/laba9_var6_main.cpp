// MPI_Graph_Comm_RU_FIXED.cpp
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
            cerr << "Требуется минимум 2 процесса!" << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Создание топологии графа "звезда"
    vector<int> index(size);    // Массив степеней вершин
    vector<int> edges;          // Список всех связей
    
    // Корректное заполнение структур для MPI_Graph_create
    index[0] = size-1;  // Процесс 0 связан со всеми остальными
    for (int i = 1; i < size; ++i) {
        index[i] = index[i-1] + 1;
        edges.push_back(i);     // Соседи для процесса 0
    }
    
    for (int i = 1; i < size; ++i) {
        edges.push_back(0);     // Соседи для остальных процессов
        index[i] = index[i-1] + 1;
    }

    MPI_Comm graph_comm;
    int reorder = 1;
    int result = MPI_Graph_create(MPI_COMM_WORLD, size, index.data(), edges.data(), reorder, &graph_comm);
    
    if (result != MPI_SUCCESS) {
        cerr << "Ошибка создания графа!" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int graph_rank;
    MPI_Comm_rank(graph_comm, &graph_rank);

    // Проверка связей
    int neighbors_count;
    MPI_Graph_neighbors_count(graph_comm, graph_rank, &neighbors_count);
    
    if (neighbors_count < 0) {
        cerr << "Некорректное количество соседей!" << endl;
        MPI_Abort(graph_comm, 1);
    }

    vector<int> neighbors(neighbors_count);
    if (neighbors_count > 0) {
        MPI_Graph_neighbors(graph_comm, graph_rank, neighbors_count, neighbors.data());
    }

    cout << "Процесс " << rank << " (новый ранг " << graph_rank << "): ";
    cout << "Соседи: ";
    for (int n : neighbors) cout << n << " ";
    cout << endl;

    // Обмен сообщениями
    if (graph_rank == 0) {
        vector<MPI_Request> requests(size-1);
        vector<int> data(size-1, 100);

        for (int i = 1; i < size; ++i) {
            MPI_Isend(&data[i-1], 1, MPI_INT, i, 0, graph_comm, &requests[i-1]);
        }

        vector<int> recv_data(size-1);
        for (int i = 0; i < size-1; ++i) {
            MPI_Recv(&recv_data[i], 1, MPI_INT, MPI_ANY_SOURCE, 0, graph_comm, MPI_STATUS_IGNORE);
        }

        cout << "Главный получил ответы: ";
        for (int val : recv_data) cout << val << " ";
        cout << endl;

        MPI_Waitall(size-1, requests.data(), MPI_STATUSES_IGNORE);
    } 
    else {
        int recv_data;
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, graph_comm, MPI_STATUS_IGNORE);
        
        int response = recv_data + graph_rank;
        MPI_Send(&response, 1, MPI_INT, 0, 0, graph_comm);
    }

    MPI_Comm_free(&graph_comm);
    MPI_Finalize();
    return 0;
}