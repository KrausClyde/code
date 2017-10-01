CFLAGS = -Wall -fPIC
CC=gcc

#OStype
ostype=$(shell uname)
CFLAGS+=$(if $(findstring Linux,ostype),,-DMAKEFILE_MACRO=\"Linux\")
CFLAGS+=$(if $(findstring Darwin,ostype),,-DMAKEFILE_MACRO=\"Mac\")

export ROOT=${pwd}
export Module_A_PATH=${ROOT}module_a
INCLUDE = -I$(ROOT)/ \
		  -I$(MODULE_A_PATH)/ 

wrap=wrap.c
SRC_origin = ${wildcard *.c}
SRC = $(if $(findstring ${wrap},SRC_origin),, $(filter-out ${wrap},$(SRC_origin)))
DIR = $(notdir ${SRC})
OBJ = $(patsubst %.c, %.o, ${SRC})

run : ${OBJ} lib_module_a.so
	@echo "build execut file"
	@echo "${ostype} CCFLAG ${CCFLAG}"
	@echo "obj " ${OBJ}
	@echo ${module}
	${CC} -o  $@  $^  -llua -lm -ldl

${OBJ}  : ${SRC}
	@echo "obj " ${OBJ}
	@echo "src " ${SRC}
	${CC} -c $^  ${CFLAGS}  ${INCLUDE}


clean :
	rm run main.o pub.o 
