CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o count.o
INCLUDE = -I.

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o PA1

main.o : main.cpp count.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
	
Complex.o : count.cpp count.h
	$(CC) count.cpp $(INCLUDE) $(CFLAGS)
	
clean:
	-rm *.o demo
