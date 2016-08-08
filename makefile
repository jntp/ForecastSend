OBJS = body.o parameters.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main 

body.o: body.cpp body.h
	$(CC) $(CFLAGS) body.cpp

parameters.o: parameters.cpp parameters.h
	$(CC) $(CFLAGS) parameters.cpp

