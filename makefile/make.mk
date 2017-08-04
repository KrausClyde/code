CFLAGS = -Wall
CC = gcc
objects = main.o pub.o func.o

run : $(objects)

$(objects) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

