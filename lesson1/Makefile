.PHONY: mk_objs mk_shared mk_static install link clean

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
OBJ_DIR := $(CUR_DIR)/objs
LIB_DIR := $(CUR_DIR)/lib
LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static
INC_FLAG := -I$(INC_DIR)
CC := gcc
STATIC_FLAG := rcs
LIST_DIR := $(LIB_SHARED) $(LIB_STATIC)
LIST_LIB := calc print
DIR_FLAG := $(foreach dir, $(LIST_DIR), -L$(dir))
LIB_FLAG := $(foreach lib, $(LIST_LIB), -l$(lib))
mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAG)

mk_shared:
	$(CC) -c -fPIC $(SRC_DIR)/calc.c -o $(OBJ_DIR)/calc.o $(INC_FLAG)
	$(CC) -shared $(OBJ_DIR)/calc.o -o $(LIB_SHARED)/libcalc.so

mk_static:
	$(CC) -c $(SRC_DIR)/print.c -o $(OBJ_DIR)/print.o $(INC_FLAG)
	ar $(STATIC_FLAG) $(LIB_STATIC)/libprint.a $(OBJ_DIR)/print.o

install:
	cp $(LIB_SHARED)/libcalc.so /usr/lib

link: mk_objs mk_shared mk_static install
	gcc $(OBJ_DIR)/main.o $(DIR_FLAG) $(LIB_FLAG) -o $(BIN_DIR)/output

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* $(LIB_STATIC)/* $(LIB_SHARED)/* 