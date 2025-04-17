#bash!

clear

mpic++ -o laba7_var4_main_bin laba7_var4_main.cpp

mpirun -np 4 ./laba7_var4_main_bin