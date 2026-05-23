.PHONY: clean all
CC=gcc
CFLAGS = -Wall
TARGET = program

all: $(TARGET)

program: main.o libsmarthome.a
	$(CC) -o program main.o -L. -lsmarthome
libsmarthome.a: smarthome.o
	ar rcs libsmarthome.a smarthome.o

main.o: src/main.c
	$(CC) -c src/main.c -o main.o -I ./include
smarthome.o: src/smarthome.c
	$(CC) -c src/smarthome.c -o smarthome.o -I ./include
clean:
	rm -rf *.o *.a program