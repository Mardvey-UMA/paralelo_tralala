//Задание 4. Проиллюстрировать возможность синхронизации в
//параллельной области значений локальных для потоков переменных(т.е.явного задания нужного значения) посредством опции copyprivate директивы single

#include <stdio.h>
#include <omp.h>
#include <locale.h>
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	int n;
#pragma omp parallel num_threads(3) private(n)
	{
		n = omp_get_thread_num(); //Каждый поток печатает свой номер
		printf("Значение n (начало): %d\n", n);
#pragma omp single copyprivate(n)
		{
			n = 100; //На выходе из секции single всем
		} //локальным переменным будет присвоено значение 100
		printf("Значение n (конец): %d\n", n);
	}
}