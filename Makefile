TARGET = lab
CC = gcc
CFLAGS = -g -Iinclude -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

GRAPH_DIR = $(SRC_DIR)/graph
TABLE_DIR = $(SRC_DIR)/table
STACK_DIR = $(SRC_DIR)/stack
CMD_DIR = $(SRC_DIR)/cmd/app
DIALOGUE_DIR = $(SRC_DIR)/dialogue
LOGIC_DIR = $(SRC_DIR)/logic

LIB_EXTENSION = .a
COMP = 

LIBRARY = $(OBJ_DIR)/lib$(TARGET)$(LIB_EXTENSION)

OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/dialogue.o $(OBJ_DIR)/logic.o
LIB_OBJ = $(OBJ_DIR)/graph.o $(OBJ_DIR)/table.o $(OBJ_DIR)/stack.o

all: dirs $(BIN_DIR)/$(TARGET)

dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(LIBRARY) $(OBJ)
	$(CC) $(OBJ) -L$(OBJ_DIR) -l$(TARGET) -o $@ $(COMP) $(CFLAGS)

$(LIBRARY): $(LIB_OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/main.o: $(CMD_DIR)/main.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/dialogue.o: $(DIALOGUE_DIR)/dialogue.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/logic.o: $(LOGIC_DIR)/logic.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/stack.o: $(STACK_DIR)/stack.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/table.o: $(TABLE_DIR)/table.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/graph.o: $(GRAPH_DIR)/graph.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)