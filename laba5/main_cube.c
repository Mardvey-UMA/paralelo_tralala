#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f4(double x, double y, double z) {
    return 1.0 / (2.0 + exp(-z) * sin(x*x - y*y));
}

double f6(double x, double y, double z) {
    return cos(x) / (1.0 + exp(x*x + y*y + z*z));
}

double f8(double x, double y, double z) {
    return 1.0 / (2.0 + exp(-x*x) * sin(y*y + z*z));
}

double serial_cube(int N, double (*f)(double, double, double)) {
    double h = 1.0 / N;
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                double x = h * (i + 0.5);
                double y = h * (j + 0.5);
                double z = h * (k + 0.5);
                sum += f(x, y, z);
            }
        }
    }
    return sum * h * h * h;
}

void parallel_cube(int N, double (*f)(double, double, double), const char* schedule, int chunk) {
    double h = 1.0 / N;
    double sum = 0.0;
    double start = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:sum) schedule(runtime)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                double x = h * (i + 0.5);
                double y = h * (j + 0.5);
                double z = h * (k + 0.5);
                sum += f(x, y, z);
            }
        }
    }
    double time = omp_get_wtime() - start;
    printf("%-8s | Time: %9.6f | Result: %.6f\n", schedule, time, sum * h * h * h);
}

void run_cube(int N) {
    printf("\nN = %d\n", N);
    
    double start_serial = omp_get_wtime();
    double sum_serial = serial_cube(N, f4);
    double time_serial = omp_get_wtime() - start_serial;
    printf("Serial   | Time: %9.6f | Result: %.6f\n", time_serial, sum_serial);
    
    omp_sched_t schedules[] = {omp_sched_static, omp_sched_dynamic, omp_sched_guided};
    char* schedule_names[] = {"Static", "Dynamic", "Guided"};
    int chunk = 0;
    
    for (int i = 0; i < 3; i++) {
        omp_set_schedule(schedules[i], chunk);
        parallel_cube(N, f4, schedule_names[i], chunk);
    }
}

int main() {
    run_cube(1000);
    run_cube(1500);
    return 0;
}