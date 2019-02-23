INC=-I /opt/X11/include
# LIBS=-L/usr/X11/lib -lX11  #unused
CC=g++
TARGET=karms
CFLAGS= -std=c++14 -Wall

OBJECTS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS=$(wildcard *.(h|hpp))

all:	build clean

build:	$(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(TARGET) $(INC) $(LIBS)
	

%.o:	%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC) $(LIBS)


clean:
	-rm -f *.o
