#include <complex>
#include <iostream>
#include <vector>
#include <ctime> 

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

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double diff = i - j;
            // Вещественная часть 1/(1 + (i-j)^2)
            double real_part = 1.0 / (1.0 + diff*diff);
            // Мнимая часть 1/(2 + (i-j)^3)
            double imag_part = 1.0 / (2.0 + diff*diff*diff);
            A[j*N + i] = complex<double>(real_part, imag_part);
        }
    }

    for (int i = 0; i < N; ++i) {
        // Правая часть 1 + 1/k^2, где k = i+1
        B[i] = complex<double>(1.0 + 1.0/((i+1)*(i+1)), 0.0);
    }

    int nrhs = 1; // Одна правая часть
    int info;
    
    clock_t start = clock();  
    
    zgesv_(&N, &nrhs, A.data(), &N, IPIV.data(), B.data(), &N, &info);
    
    double elapsed = double(clock() - start) / CLOCKS_PER_SEC;
    
    cout << "N=" << N << endl;
    cout << "Time=" << elapsed << " Sec" << endl;
    cout << "info=" << info << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    for (int N = 256; N <= 8096; N *= 2) {
        Tst_Func(N);
    }

    return 0;
}