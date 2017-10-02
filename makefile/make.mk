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
	@echo "FLAG ${FLAG} ${FLAG1} ostype ${ostype}"
	@echo "build execut file"
	@echo "${ostype} CFLAGS ${CFLAGS}"
	@echo "obj " ${OBJ}
	@echo ${module}
	${CC} -o  $@  $^  -llua -lm -ldl

${OBJ}  : ${SRC}
	@echo "obj " ${OBJ}
	@echo "src " ${SRC}
	${CC} -c $^  ${CFLAGS}  ${INCLUDE}


clean :
	rm run main.o pub.o 
