run : main.o func.o pub.o fprintf.o lua_func.o wrap.o
	#gcc -Wl,--wrap,malloc -Wl,--wrap,free -o run main.o  pub.o lua_func.o  libfunc.so -llua -lm -ldl
	gcc -Wl,-alias,__Z3malloc,__Z8wrap_malloc -o run main.o  pub.o lua_func.o  libfunc.so -llua -lm -ldl

main.o : main.c func.h pub.h
	gcc -Wall -c main.c

func.o : func.c func.h
	gcc -Wall -c func.c

pub.o : pub.c pub.h
	gcc -Wall -c pub.c

#fprintf.o : fprintf.c
#	cc -Wall -c fprintf.c

lua_func.o : lua_func.c lua_func.h test.lua
	gcc -Wall -c  lua_func.c

libfunc.so : fprintf.c func.c func.h pub.h wrap.c
	#gcc -Wl,--wrap,malloc -Wl,--wrap,free -shared func.c fprintf.c -o libfunc.so
	gcc -Wl,-alias,__Z3malloc,__Z8wrap_malloc -shared func.c fprintf.c -o libfunc.so    

wrap.o : wrap.c
	gcc -Wall -c wrap.c
clean :
	rm run main.o func.o pub.o
