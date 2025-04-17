//Задание 6. Разработать программу, иллюстрирующую возможность реализации конечного(неитеративного) параллелизма при помощи
//директив omp sections и omp section

#include <stdio.h>
#include <omp.h>
#include <locale.h>
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	int n;
#pragma omp parallel num_threads(3) private(n)
	{
		n = omp_get_thread_num();
#pragma omp sections
		{
#pragma omp section
			{
				printf("Первая секция, поток %d\n", n);
			}
#pragma omp section
			{
				printf("Вторая секция, поток %d\n", n);
			}
#pragma omp section
			{
				printf("Третья секция, поток %d\n", n);
			}
#pragma omp section
			{
				printf("Четвертая секция, поток %d\n", n);
			}
#pragma omp section
			{
				printf("Пятая секция, поток %d\n", n);
			}
		}
		printf("Параллельная область, поток %d\n", n);
	}
}