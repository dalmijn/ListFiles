# File extensions
OBJ_EXT		:= .o
SOL_EXT		:= .exe

# Paths
MK_PATH	 	:= $(abspath $(lastword $(MAKEFILE_LIST)))
CWD_DIR 	:= $(patsubst %/,%,$(dir $(MK_PATH)))
SRC_DIR		:= ${CWD_DIR}/src
INTER_DIR	:= ${CWD_DIR}/bin/intermediates
SOL_DIR		:= ${CWD_DIR}/bin/Release
SOL_NAME	:= listfiles${SOL_EXT}

# Commands
MKDIR_COMMAND := mkdir

# Compilers
CC  := gcc
CXX := g++
CXX := ${CXX}

# Compiler flags
COMP_FLAG		:= -c
DEBUG_FLAG 		:= -g
OBJ_FLAG		:= -o
OPT_FLAG 		:= -O2
SYMBOL_FLAG 	:= -s
STD_FLAG		:= -std=c++17
WARNING_FLAG	:= -Wall

# Linker flags
RUNTIME_OPT_FLAG	:= -flto

# Mode Settings
CXX_FLAGS	:= ${STD_FLAG} ${WARNING_FLAG} ${OPT_FLAG} ${SYMBOL_FLAG} ${RUNTIME_OPT_FLAG}
LINK_FLAGS 	:= ${OPT_FLAG} ${SYMBOL_FLAG} ${RUNTIME_OPT_FLAG}

# Targets
Objects0=$(INTER_DIR)/main$(OBJ_EXT)
Objects=$(Objects0)

# Actions
.PHONY: all make_directories compiling linking

all: make_directories ${Objects} linking
	${CXX} --version
	@echo ${SRC_DIR}

compiling:
$(INTER_DIR)/main$(OBJ_EXT): ${SRC_DIR}/main.cpp
	${CXX} ${COMP_FLAG} "${SRC_DIR}/main.cpp" ${CXX_FLAGS} ${OBJ_FLAG} $(INTER_DIR)/main$(OBJ_EXT)

linking:
	${CXX} ${LINK_FLAGS} ${OBJ_FLAG} ${SOL_DIR}/${SOL_NAME} ${Objects}

make_directories:
	@if not exist "${INTER_DIR}" ${MKDIR_COMMAND} "${INTER_DIR}"
	@if not exist "${SOL_DIR}" ${MKDIR_COMMAND} "${SOL_DIR}"
	