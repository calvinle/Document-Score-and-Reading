CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o
INCLUDE = -I.

demo : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o PA2

main.o : main.cpp
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
	
clean:
	-rm *.o demo
