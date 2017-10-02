CFLAGS = -Wall -fPIC
CCFLAG = -Wl,--wrap,malloc -Wl,--wrap,free
CC=gcc

#OStype
ostype=$(shell uname)
CFLAGS+=$(if $(findstring ${ostype},"Darwin"), -DMAKEFILE_MACRO=\"Mac\")
CFLAGS+=$(if $(findstring ${ostype},"GNU/Linux"),-DMAKEFILE_MACRO=\"Linux\")
CFLAGS+=$(if $(findstring ${ostype},"GNU/Linux") ,${CCFLAG})

FLAG=$(findstring \"Darwin\",${ostype})
FLAG1=$(if FLAG, "DDDD")
export ROOT=${shell pwd}
export Module_A_PATH=${ROOT}/module_a

MODULE=module_a
module=${ROOT}/lib_$(MODULE).so

INCLUDE = -I$(ROOT)/ \
		  -I$(Module_A_PATH)/ 

#include /home/anlian/code/makefile/module_a/makefile_module_a.mk

wrap=wrap.c
SRC_origin = ${wildcard *.c}
#SRC = $(if $(findstring ${wrap},SRC_origin),, $(filter-out ${wrap},$(SRC_origin)))
SRC = $(if $(findstring ${ostype},"Darwin"), $(filter-out ${wrap},${SRC_origin}), ${SRC_origin})
DIR = $(notdir ${SRC})
OBJ = $(patsubst %.c, %.o, ${SRC})

run : ${OBJ} ${module}
	@echo "FLAG ${FLAG} ${FLAG1} ostype ${ostype}"
	@echo "build execut file"
	@echo "SRC: ${SRC_origin};${SRC} obj:${OBJ}"
	@echo "PATH ROOT ${ROOT} Module_A_PATH ${Module_A_PATH} module ${module}"
	@echo "${ostype} CFLAGS ${CFLAGS}"
	${CC} -o  $@  $^ ${CFLAGS} -llua -lm -ldl

${OBJ}  : ${SRC}
	${CC} -c $^  ${CFLAGS}  ${INCLUDE}

.PHONY : clean
clean :
	rm -f *.o 


