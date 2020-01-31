# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica1_B

BIN = bin
SRC = src
OBJ = obj
LIB = lib
INCLUDE = include

CC = g++
CCFLAGS = -std=c++11 -O3

ifndef NOWARN
	CCFLAGS += -Wall -Wextra
else
	CCFLAGS += -w
endif

GLFLAGS = -lGL -lGLU -lglut

MAINDEPENDENCIES = $(OBJ)/objetos_B.o $(OBJ)/main.o $(OBJ)/file_ply_stl.o \
$(OBJ)/Mano.o

TARGETS = clean $(BIN)/main

all: $(TARGETS)

$(BIN)/main: $(MAINDEPENDENCIES)
	$(CC) $^ $(GLFLAGS) $(CCFLAGS) -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(OBJ)/objetos_B.o: $(SRC)/objetos_B.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(OBJ)/Mano.o: $(SRC)/Mano.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)



# Clean
.PHONY: clean

clean:
	-rm $(BIN)/* $(OBJ)/*
