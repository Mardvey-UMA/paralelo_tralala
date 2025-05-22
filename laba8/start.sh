#bash!

clear

mpic++ -o laba8_var4_main_bin laba8_var4_main.cpp

mpirun -np 4 ./laba8_var4_main_bin