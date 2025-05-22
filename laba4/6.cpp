//Задание 6. То же самое, но с попыткой установить блокировку, и,
//если секция уже заблокирована, с печатью ожидающими потоками с интервалом в 1 секунду сообщения о том, что секция блокирована.Использовать функцию omp_test_lock.
//(При помощи блокировки(обеспечивается стандартными функциями OpenMP omp_init_lock, omp_set_lock, omp_unset_lock),
//	добиться того, чтобы сообщения, печатаемые в разных потоках в параллельной секции, не перемежались друг с другом.Для имитации вычислений использовать функцию sleep(Sleep в ОС Windows))

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
void sleep(int Secnds)
{
	Sleep(1000 * Secnds);
}
#else
#include <unistd.h>
#endif
omp_lock_t lock;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	int n;
	omp_init_lock(&lock);
#pragma omp parallel num_threads(4) private (n)
	{
		n = omp_get_thread_num();
		while (!omp_test_lock(&lock))
		{
			printf("Секция закрыта, поток %d\n", n);
			sleep(2);
		}
		printf("Начало закрытой секции, поток %d\n", n);
		sleep(2 + 3 * ((n + 1) % 2));
		printf("Конец закрытой секции, поток %d\n", n);
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
}
