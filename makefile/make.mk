CFLAGS = -Wall -fPIC
CC=gcc

export ROOT=${pwd}
export Module_A_PATH=${ROOT}module_a
INCLUDE = -I$(ROOT)/ \
		  -I$(MODULE_A_PATH)/ \

SRC = ${wildcard *.c}
DIR = $(notdir ${SRC})
OBJ = $(patsubst %.c, %.o, ${SRC})

run : ${OBJ} lib_module_a.so
	@echo "build execut file"
	@echo "obj " ${OBJ}
	${CC} -o $@  $^  -llua -lm -ldl

${OBJ}  : ${SRC}
	@echo "obj " ${OBJ}
	@echo "src " ${SRC}
	${CC} -c $^  ${CFLAGS}  ${INCLUDE}


clean :
	rm run main.o pub.o wrap.o
