CFLAGS = -Wall -fPIC
export BuildPATH=$(pwd)
export ROOT=${pwd}..
MODULE=module_a
module=${ROOT}/lib_$(MODULE).so

INCLUDE = -I$(ROOT)/ \
		  -I$(BuildPATH)/ \

#SRC = $(shell find ${BuildPATH} -name "*.c")
#OBJ = $(foreach obj, ${SRC}, $patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, $(obj))
#DIR = $(notdir ${SRC})
#OBJ = $(patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, ${DIR})	

SRC = ${wildcard ${BuildPATH}*.c}
DIR = $(notdir ${SRC})
OBJ = $(patsubst ${BuildPATH}%.c, ${BuildPATH}%.o, ${SRC})
#OBJ = func.o
${module} : ${OBJ}
	@echo "build ${module}"
	@echo "SRC " ${SRC}
	@echo "OBJ " ${OBJ}
	gcc -shared -o $@  $^  ${CFLAGS} ${INCLUDE}
	@echo "$(module) built"

${BuildPATH}%.o : ${BuildPATH}%.c
	@echo "build OBJ"
	gcc -c $^ ${CFLAGS} $(INCLUDE)
