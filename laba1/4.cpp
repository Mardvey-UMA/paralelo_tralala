//Задание 4. То же самое, что в задании 3, но с принудительной
//установкой нужного числа потоков (Разработать программу, в которой при входе в параллельную область каждый из потоков OpenMP должен распечатать сообщение).

#include <stdio.h>
#include <math.h>
#include <omp.h>
int main(int argc, char* argv[])
{
	printf("Serial region 1\n Number of OMP Threads=");
	int N;
	scanf("%d", &N);
	printf("\n");
	N = abs(N);
	N = N ? N : 1;
	omp_set_dynamic(0); //Запрещает динамическую установку числа
	//потоков в следующих параллельных областях
	omp_set_num_threads(N); //Задает нужное число потоков
	//в следующей параллельной области
#pragma omp parallel
	{
			printf("Parallel region 1\n");
	}
	printf("Serial region 2\n");
	omp_set_dynamic(1); //Разрешает динамическую установку числа
	//потоков в следующих параллельных областях
	omp_set_num_threads(N);
#pragma omp parallel
	{
		printf("Parallel region 2\n");
	}
	printf("Serial region 3\n");
}
