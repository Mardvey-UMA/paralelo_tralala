//Задание 8. Проиллюстрировать возможности директив стандарта
//OpenMP 3.0 omp task и omp taskwait для выделения и выполнения отдельных независимых задач, т.е.для распараллеливания в стиле «портфель задач», пригодном в ситуации, когда время решения отдельной подзадачи плохо предсказуемо.Следует учитывать, что по умолчанию подзадача(task) связывается с потоком, который первый ее начинает исполнять(не с тем, который ее создал).Поскольку создание малых подзадач
//(task) неэффективно, для имитации вычислений использовать функцию
//задержки sleep(unsigned long) (либо Sleep(unsigned long) для Windows).

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
void sleep(int Secnds)
{
	Sleep(1000 * Secnds);
}
#else
#include <unistd.h>
#endif
#define NNN 15
void My_Task(int k)
{
#ifdef _OPENMP
		int n = omp_get_thread_num();
#else
		int n = 0;
#endif
	printf("k= %d Поток %d начал вычисления\n", k, n);
	sleep((((k + 6) % 7) + ((k + 3) % 4)));//имитируем вычисления
	printf("k= %d Поток %d выполнил вычисления\n", k, n);
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	double Time = clock();
#pragma omp parallel
	{
#pragma omp single
		{
			for (int k = 0; k < NNN; k++) {
#pragma omp task
				My_Task(k);
			}
#pragma omp taskwait
		}
	}
	printf("Подзадачи завершены\n");
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	printf("Время: %f сек.\n", Time);
}
