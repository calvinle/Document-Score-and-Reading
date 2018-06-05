CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = main.o split.o cl.o word.o tfidf.o
INCLUDE = -I.

PA7 : $(OBJS)
	$(CC) -Ofast $(OBJS) $(INCLUDE) $(LFLAGS) -o PA8

main.o : main.cpp split.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
	
split.o	: split.cpp split.h
	$(CC) split.cpp $(INCLUDE) $(CFLAGS)

cl.o	: cl.cpp cl.h
	$(CC) cl.cpp $(INCLUDE) $(CFLAGS)

word.o	:	word.cpp word.h
	$(CC) word.cpp $(INCLUDE) $(CFLAGS)
	
tfidf.o	:	tfidf.cpp tfidf.h
	$(CC) tfidf.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o PA8
