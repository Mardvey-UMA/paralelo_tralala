//Задание 4. Частным случаем критических секций является директива omp atomic, непосредственно воздействующая на следующий за
//ней оператор присваивания.Используя данную директиву, написать программу, которая подсчитывает число потоков в параллельной области.

#include <stdio.h>
#include <omp.h>
#include <locale.h>
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	int count = 0;
#pragma omp parallel
	{
#pragma omp atomic
		count++;
	}
	printf("Число потоков: %d\n", count);
}