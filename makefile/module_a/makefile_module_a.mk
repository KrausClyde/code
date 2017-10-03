CFLAGS ?= -Wall -fPIC
#export BuildPATH=${shell pwd}
#export ParentPATH=${BuildPATH}/..
BuildPATH?=${ROOT}/module_a
BuildPATH?=${shell pwd}
ParentPATH?=${ROOT}
ParentPATH?=${BuildPATH}/..
MODULE=module_a
module_name=${ParentPATH}/lib_$(MODULE).so

INCLUDE = -I$(ParentPATH)/ \
		  -I$(BuildPATH)/ \

#SRC = $(shell find ${BuildPATH} -name "*.c")
#OBJ = $(foreach obj, ${SRC}, $patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, $(obj))
#DIR = $(notdir ${SRC})
#OBJ = $(patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, ${DIR})	

Module_A_SRC = ${wildcard ${BuildPATH}/*.c}
Module_A_DIR = $(notdir ${Module_A_SRC})
Module_A_OBJ = $(patsubst %.c, %.o, ${Module_A_DIR})
#OBJ = func.o
${module_name} : ${Module_A_OBJ}
	@echo "build ${module_name}"
	@echo "SRC " ${Module_A_SRC} "OBJ" ${OBJ}
	@echo "Module_A PATH ROOT:${ParentPATH}  BuildPATH:${BuildPATH}"
	gcc -shared -o $@  $^  ${CFLAGS} ${INCLUDE}
	@echo "$(module_name) built"

${Module_A_OBJ} : ${Module_A_SRC}
	@echo "build OBJ"
	@echo "MODULE CFLAGS ${CFLAGS} SRC ${Module_A_SRC}"
	gcc -c $^ ${CFLAGS} $(INCLUDE)

.PHONY : clean
clean :
	rm -f ${Module_A_OBJ}
