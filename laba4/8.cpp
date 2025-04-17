//Задание 8. Обеспечить распараллеливание вычислений на основе
//OpenMP при выполнении операции умножения матриц достаточно большого размера.Исследовать эффективность распараллеливания при использовании различных компиляторов#include <iostream>
#include <time.h>
#define N 1024
double a[N][N], b[N][N], c[N][N];
using namespace std;
int main()
{
		int i, j, k;
	double Tms;
	// инициализация матриц
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			a[i][j] = b[i][j] = i * j;
	Tms = clock();
	// основной вычислительный блок
#pragma omp parallel for shared(a, b, c) private(i, j, k)
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			c[i][j] = 0.0;
			for (k = 0; k < N; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;
	cout << "Time=" << Tms << " sec" << endl;
}