run : main.o func.o pub.o fprintf.o lua_func.o wrap.o
	cc -Wl,--wrap,malloc -Wl,--wrap,free -o run main.o  pub.o lua_func.o  libfunc.so -llua -lm -ldl

main.o : main.c func.h pub.h
	cc -Wall -c main.c

func.o : func.c func.h
	cc -Wall -c func.c

pub.o : pub.c pub.h
	cc -Wall -c pub.c

#fprintf.o : fprintf.c
#	cc -Wall -c fprintf.c

lua_func.o : lua_func.c lua_func.h test.lua
	cc -Wall -c  lua_func.c

libfunc.so : fprintf.c func.c func.h pub.h wrap.c
	cc -Wl,--wrap,malloc -Wl,--wrap,free -shared func.c fprintf.c -o libfunc.so
    
wrap.o : wrap.c
    cc -Wall -c wrap.c
clean :
	rm run main.o func.o pub.o
