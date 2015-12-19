OBJ_DIR = obj
SRC_DIR1 = .
SRC_DIR2 = src
SRC = $(wildcard $(SRC_DIR1)/*.cpp) $(wildcard $(SRC_DIR2)/*.cpp)
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
VPATH=.:src


RELEASE_DIR = bin
RELEASE_DEBUG_DIR = binDebug
EXEC =$(RELEASE_DIR)/timeShortest
EXEC_DEBUG =$(RELEASE_DEBUG_DIR)/timeShortest


CC = g++
CFLAGS = -Wall -Werror -O1
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS_DEBUG = -g -lsfml-graphics-d -lsfml-window-d -lsfml-system-d


all: createDir $(EXEC)

makeDebug: $(EXEC_DEBUG)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC_DEBUG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS_DEBUG)

$(OBJ_DIR)/%.o: %.cpp
	echo $(SRC)
	$(CC) -o $@ -c $< $(CFLAGS)

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(RELEASE_DEBUG_DIR)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(RELEASE_DEBUG_DIR)

