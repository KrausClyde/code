CFLAGS = -Wall -fPIC
export BuildPATH=${shell pwd}
export ParentPATH=${BuildPATH}/..
MODULE=module_a
module=${ParentPATH}/lib_$(MODULE).so

INCLUDE = -I$(ParentPATH)/ \
		  -I$(BuildPATH)/ \

#SRC = $(shell find ${BuildPATH} -name "*.c")
#OBJ = $(foreach obj, ${SRC}, $patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, $(obj))
#DIR = $(notdir ${SRC})
#OBJ = $(patsubst ${BuildPATH}/.%c, ${BuildPATH}/%.o, ${DIR})	

Module_A_SRC = ${wildcard *.c}
Module_A_DIR = $(notdir ${Module_A_SRC})
Module_A_OBJ = $(patsubst %.c, %.o, ${Module_A_SRC})
#OBJ = func.o
${module_a} : ${Module_A_OBJ}
	@echo "build ${module_a}"
	@echo "SRC " ${Module_A_SRC} "OBJ" ${OBJ}
	@echo "PATH ROOT:${ParentPATH}  BuildPATH:${BuildPATH}"
	gcc -shared -o $@  $^  ${CFLAGS} ${INCLUDE}
	@echo "$(module_a) built"

${Module_a_OBJ} : ${Module_A_SRC}
	@echo "build OBJ"
	gcc -c $^ ${CFLAGS} $(INCLUDE)

.PHONY : clean
clean :
	rm -f *.o
