#Comando para comentar todo lo selecionado: Windows: Control + / y para Mac: Command + /
#Makefile para Linux

# # # Compilador y flags
# CXX := g++
# CXXFLAGS := -std=c++11 -Wall -I./include

# # Directorios
# SRC_DIR := src
# BUILD_DIR := build
# BIN_DIR := bin

# # Archivos fuente
# SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# # Archivo de prueba
# TEST_FILE := test.cpp
# TEST_OBJ := $(BUILD_DIR)/test.o

# # Nombre del ejecutable
# TARGET := $(BIN_DIR)/clustering_program

# # Regla principal
# all: $(TARGET)

# # Crear el ejecutable
# $(TARGET): $(OBJ_FILES) $(TEST_OBJ) | $(BIN_DIR)
# 	$(CXX) $(OBJ_FILES) $(TEST_OBJ) -o $@

# # Compilar archivos de src/
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Compilar test.cpp
# $(TEST_OBJ): $(TEST_FILE) | $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Crear directorios si no existen
# $(BUILD_DIR):
# 	mkdir -p $@

# $(BIN_DIR):
# 	mkdir -p $@

# # Limpiar archivos compilados
# clean:
# 	rm -rf $(BUILD_DIR) $(BIN_DIR)

# # Recompilar desde cero
# rebuild: clean all

# # Ejecutar el programa
# run: $(TARGET)
# 	./$(TARGET)

# .PHONY: all clean rebuild run



#Comando para comentar todo lo selecionado: Windows: Control + / y para Mac: Command + /

#Makefile Mac 

# Compilador y flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I./include
LDFLAGS :=

# Directorios
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Archivos fuente
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Archivo de prueba
TEST_FILE := test.cpp
TEST_OBJ := $(BUILD_DIR)/test.o

# Nombre del ejecutable
TARGET := $(BIN_DIR)/clustering_program

# Regla principal
all: $(TARGET)

# Crear el ejecutable
$(TARGET): $(OBJ_FILES) $(TEST_OBJ) | $(BIN_DIR)
	$(CXX) $(OBJ_FILES) $(TEST_OBJ) -o $@ $(LDFLAGS)

# Compilar archivos de src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar test.cpp
$(TEST_OBJ): $(TEST_FILE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Recompilar desde cero
rebuild: clean all

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
