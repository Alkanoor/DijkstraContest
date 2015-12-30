OBJ_DIR = obj
SRC_DIR1 = .
SRC_DIR2 = src
SRC = $(wildcard $(SRC_DIR2)/*.cpp) $(wildcard $(SRC_DIR1)/*.cpp)
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
VPATH=.:src


RELEASE_DIR = bin
RELEASE_DEBUG_DIR = binDebug
EXEC =$(RELEASE_DIR)/myAlgo
EXEC_DEBUG =$(RELEASE_DEBUG_DIR)/myAlgo


CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11
LDFLAGS =
LDFLAGS_DEBUG = -g


all: createDir $(EXEC)

makeDebug: $(EXEC_DEBUG)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC_DEBUG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS_DEBUG)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(RELEASE_DEBUG_DIR)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(RELEASE_DEBUG_DIR)

