.PHONY: server client clear

CC := gcc
FLAGS := -c 
CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs
INC_FLAG := -I$(INC_DIR)
DIR_FLAG := -L$(OBJ_DIR)

make_ultilites:
	$(CC) $(FLAGS) $(SRC_DIR)/chat_func.c -o $(OBJ_DIR)/chat_func.o $(INC_FLAG)
	$(CC) $(FLAGS) $(SRC_DIR)/handle_error.c -o $(OBJ_DIR)/handle_error.o $(INC_FLAG)
	
make_objs: make_ultilites
	$(CC) $(FLAGS) $(SRC_DIR)/server_stream.c -o $(OBJ_DIR)/server_stream.o $(INC_FLAG)
	$(CC) $(FLAGS) $(SRC_DIR)/client_stream.c -o $(OBJ_DIR)/client_stream.o $(INC_FLAG)

server: make_objs
	$(CC) $(OBJ_DIR)/server_stream.o $(OBJ_DIR)/handle_error.o $(OBJ_DIR)/chat_func.o -o $(CUR_DIR)/server
	rm -rf $(OBJ_DIR)/*.o

client: make_objs
	$(CC) $(OBJ_DIR)/client_stream.o $(OBJ_DIR)/handle_error.o $(OBJ_DIR)/chat_func.o -o $(CUR_DIR)/client
	rm -rf $(OBJ_DIR)/*.o


clear:
	rm -rf $(CUR_DIR)/server $(CUR_DIR)/client 
	rm -rf $(OBJ_DIR)/*