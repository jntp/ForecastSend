OBJS = body.o parameters.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main 

main.o: main.cpp parameters.h
	$(CC) $(CFLAGS) main.cpp 

body.o: body.cpp body.h
	$(CC) $(CFLAGS) body.cpp

parameters.o: parameters.cpp parameters.h
	$(CC) $(CFLAGS) parameters.cpp

