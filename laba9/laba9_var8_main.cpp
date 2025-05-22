// MPI_Collective_Example_RU.cpp
#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double value;
    const int root = 0;

    // Процесс 0 инициализирует значение
    if (rank == root) {
        value = 0.0; // Начальное значение
        cout << "Процесс 0: исходное значение = " << fixed << setprecision(2) << value << endl;
    }

    // Широковещательная рассылка значения
    MPI_Bcast(&value, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);

    // Каждый процесс добавляет свой ранг
    value += rank;
    cout << "Процесс " << rank << ": после добавления ранга = " << value << endl;

    // Сбор модифицированных значений
    double* gathered_data = nullptr;
    if (rank == root) {
        gathered_data = new double[size];
    }

    MPI_Gather(&value, 1, MPI_DOUBLE, 
               gathered_data, 1, MPI_DOUBLE, 
               root, MPI_COMM_WORLD);

    // Вывод собранных данных
    if (rank == root) {
        cout << "\nПроцесс 0 собрал данные: ";
        for (int i = 0; i < size; ++i) {
            cout << gathered_data[i] << " ";
        }
        cout << endl;
        delete[] gathered_data;
    }

    MPI_Finalize();
    return 0;
}