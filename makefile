OBJS = body.o parameters.o main.o
ROBJS = Utils.o Rest.o TwiML.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
RFLAGS = -lcurl -lssl -lcrypto 

main: $(OBJS) $(ROBJS)
	$(CC) $(LFLAGS) $(OBJS) $(ROBJS) -o main.exe $(RFLAGS)

main.o: main.cpp parameters.h
	$(CC) $(CFLAGS) main.cpp 

body.o: body.cpp body.h
	$(CC) $(CFLAGS) body.cpp

parameters.o: parameters.cpp parameters.h
	$(CC) $(CFLAGS) parameters.cpp

SMS: SMS.cpp $(ROBJS)
	$(CC) $(LFLAGS) $(ROBJS) SMS.o -o SMS.exe $(RFLAGS)

SMS.o: SMS.cpp Utils.h Rest.h TwiML.h
	$(CC) $(CFLAGS) SMS.cpp

