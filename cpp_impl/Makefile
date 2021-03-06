# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall


Main: main.o sim.o actors.o utils.o
	$(CC) $(CFLAGS) -o Main main.o sim.o actors.o utils.o $$(sdl2-config --cflags --libs)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

actors.o: actors.cpp
	$(CC) $(CFLAGS) -c actors.cpp

sim.o: sim.cpp
	$(CC) $(CFLAGS) -c sim.cpp

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp

clean:
	rm *.o Main