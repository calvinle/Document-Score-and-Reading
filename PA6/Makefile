CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o split.o word.o tfidf.o
INCLUDE = -I.

PA5 : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o PA6

main.o : main.cpp split.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
	
split.o	: split.cpp split.h
	$(CC) split.cpp $(INCLUDE) $(CFLAGS)

word.o	:	word.cpp word.h
	$(CC) word.cpp $(INCLUDE) $(CFLAGS)
	
tfidf.o	:	tfidf.cpp tfidf.h
	$(CC) tfidf.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o PA6
