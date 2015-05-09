
CC=g++
CFLAGS=-std=c++11 -c
LFLAGS=-lGL -lGLU -lglut

SRC_FILES=Graphics Line Rectangle Polygon
TEST_FILES=PolygonTest

SRC_DIR=src/
OBJ_DIR=obj/
BIN_DIR=bin/
TEST_DIR=tests/

all: create-dir build-src build-tests

build-src: create-dir $(SRC_FILES)

build-tests: build-src $(TEST_FILES)

% : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)$@.o

% : $(SRC_DIR)$(TEST_DIR)%.cpp build-src
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)$(TEST_DIR)$@.o
	$(CC) $(OBJ_DIR)*.o $(OBJ_DIR)$(TEST_DIR)$@.o -o $(BIN_DIR)$(TEST_DIR)$@.out $(LFLAGS)

create-dir:
	mkdir -p obj/tests/
	mkdir -p bin/tests/

clean:
	rm -r $(OBJ_DIR) $(BIN_DIR)
