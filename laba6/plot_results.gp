set terminal pngcairo size 800,600 enhanced font 'Verdana,12'
set output 'performance_comparison.png'

set title "Сравнение производительности алгоритмов"
set xlabel "Метод"
set ylabel "Время (мс)"
set style data histogram
set style histogram clustered
set style fill solid border -1
set boxwidth 0.8
set grid y

plot 'results.csv' using 3:xtic(1) title "Последовательная" lc rgb "#3498db", \
     '' using 3:xtic(1) title "Параллельная" lc rgb "#e74c3c"
