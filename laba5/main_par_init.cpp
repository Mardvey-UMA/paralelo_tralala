#include <complex>
#include <iostream>
#include <vector>
#include <omp.h> 

extern "C" void zgesv_(
    int* n,              // Размер матрицы (число уравнений)
    int* nrhs,           // Число правых частей
    std::complex<double>* a,  // Матрица коэффициентов
    int* lda,            // Leading dimension матрицы A
    int* ipiv,           // Массив для хранения перестановок
    std::complex<double>* b,  // Вектор правой части/решения
    int* ldb,            // Leading dimension вектора b
    int* info            // Код завершения
);

using namespace std;

void Tst_Func(int N) {
    vector<complex<double>> A(N*N);
    vector<complex<double>> B(N);
    vector<int> IPIV(N);

    omp_set_num_threads(omp_get_max_threads());
    
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double diff = i - j;  // Разность индексов
            double real_part = 1.0 / (1.0 + diff*diff);
            double imag_part = 1.0 / (2.0 + diff*diff*diff);
            A[j*N + i] = complex<double>(real_part, imag_part);
        }
    }

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        // Правая часть по заданию: 1 + 1/k^2, где k = i+1 (т.к. индексация с 0)
        B[i] = complex<double>(1.0 + 1.0/((i+1)*(i+1)), 0.0);
    }

    int nrhs = 1;  // Одна правая часть
    int info;      // Переменная для кода возврата
    
    double start_time = omp_get_wtime(); 
    
    zgesv_(&N, &nrhs, A.data(), &N, IPIV.data(), B.data(), &N, &info);
    
    double elapsed = omp_get_wtime() - start_time;  
		
		cout << "N=" << N << endl;
		cout << "Time="<<elapsed<<" Sec"<<endl;
		cout << "info="<<info<<endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    omp_set_num_threads(omp_get_max_threads());
    
    cout << "Доступно потоков: " << omp_get_max_threads() << endl << endl;

    for (int N = 256; N <= 4096; N *= 2) {
        Tst_Func(N);
    }

    return 0;
}