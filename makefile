#
## CSCI 370: Sample Makefile for OCCI compilation
#

CFLAGS = -I/usr/local/lib/Oracle/instantclient_11_2/sdk/include
LFLAGS = -L/usr/local/lib/Oracle/instantclient_11_2 -locci -lociei
all: GymAccess 

GymAccess.o: GymAccess.cpp
	g++ -c $(CFLAGS) GymAccess.cpp

GymAccess: GymAccess.o
	g++ $(LFLAGS) -o GymAccess GymAccess.o

clean:
	rm -f *.o GymAccess 


