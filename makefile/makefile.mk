run : main.o func.o pub.o fprintf.o
	cc -o run main.o func.o pub.o fprintf.o

main.o : main.c func.h pub.h
	cc -Wall -c main.c

func.o : func.c func.h
	cc -Wall -c func.c

pub.o : pub.c pub.h
	cc -Wall -c pub.c

fprintf.o : fprintf.c
	cc -Wall -c fprintf.c

clean :
	rm run main.o func.o pub.o
