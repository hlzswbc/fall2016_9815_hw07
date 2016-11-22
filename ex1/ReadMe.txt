g++ -c -Wall Process1.cpp 
g++ -L /lib Process1.o -o PROCESS1
g++ -L /lib Process1.o -o PROCESS1 -lrt -lpthread
g++ -c -Wall Process2.cpp
g++ -L /lib Process2.o -o PROCESS2 -lrt -lpthread
./PROCESS1

//another terminal
./PROCESS2