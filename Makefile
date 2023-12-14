CC = gcc
DOC = doxygen
CFLAGS = -g -Og -I ./include -I ./include/image # -ansi -Wall -Wextra -pedantic 
LIBS = -L ./lib -limage64

INCLUDES_IMAGE = include/image.h include/image/objet.h include/image/exit_if.h include/image/classe.h include/image/point.h include/image/move_type.h include/image/type_obj.h
OBJ_DIR = bin/obj
DOC_DIR = documentation/Doxyfile
RM = rm -f


.PHONY = all tests clean distclean doc

all: prog

tests: testPartitionImage testMomentImage testRag testPerformMerge

include src/Makefile
include test/Makefile

clean:
	-@$(RM) $(OBJ_DIR)/*
	-@echo "object file remove"

distclean: clean docclean
	-@$(RM) bin/prog
	-@$(RM) bin/test/*
	-@echo "executable file remove"

doc:
	-@$(DOC) $(DOC_DIR)
	-@echo "doc file generated"

docclean:
	-@$(RM) -r documentation/html
	-@echo "doc file remove"