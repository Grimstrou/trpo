APP_NAME = geometry
LIB_NAME = libgeometry
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -I $(SRC_DIR)
LDFLAGS = -L $(OBJ_PATH)/$(LIB_NAME) -l$(APP_NAME) -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

OBJ_PATH = $(OBJ_DIR)/$(SRC_DIR)
APP_PATH = $(BIN_DIR)/$(APP_NAME)

all: $(APP_PATH)

$(OBJ_PATH)/functions.o: $(SRC_DIR)/$(LIB_NAME)/functions.c  $(SRC_DIR)/$(LIB_NAME)/functions.h
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_PATH)/$(LIB_NAME)/$(LIB_NAME).a: $(OBJ_PATH)/functions.o
	ar rcs $@ $^

$(APP_PATH): $(OBJ_PATH)/$(APP_NAME)/main.o
	$(CC) $^ -o $(APP_PATH) $(LDFLAGS)

$(OBJ_PATH)/$(APP_NAME)/main.o: $(OBJ_PATH)/$(LIB_NAME)/$(LIB_NAME).a $(SRC_DIR)/$(APP_NAME)/main.c
	rm -f $(OBJ_DIR)/$(LIB_PATH)/*.d
	rm -f $(OBJ_DIR)/$(LIB_PATH)/*.o
	$(CC) $(CFLAGS) $^ -o $@ -L obj/src/libgeometry -lgeometry

run:
	$(APP_PATH) data.txt

clean:
	rm -f $(APP_PATH)
	rm -f $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.o
	rm -f $(OBJ_DIR)/$(LIB_PATH)/$(LIB_NAME).a
	rm -f $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.d
	rm -f $(OBJ_DIR)/$(LIB_PATH)/*.d
	rm -f $(OBJ_DIR)/$(LIB_PATH)/*.o