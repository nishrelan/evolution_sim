# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -g -std=c++0x -O2


Main.out: main.o sim.o actors.o utils.o vis.o
	$(CC) $(CFLAGS) -o Main.out main.o sim.o actors.o utils.o vis.o $$(sdl2-config --cflags --libs)

main.o: main.cpp actors.h 
	$(CC) $(CFLAGS) -c main.cpp

actors.o: actors.cpp actors.h
	$(CC) $(CFLAGS) -c actors.cpp

sim.o: sim.cpp sim.h actors.h
	$(CC) $(CFLAGS) -c sim.cpp

utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c utils.cpp

vis.o: vis.cpp vis.h actors.h
	$(CC) $(CFLAGS) -c vis.cpp

clean:
	rm *.o *.out