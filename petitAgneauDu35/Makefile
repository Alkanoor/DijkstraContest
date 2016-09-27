CC := gcc
CFLAGS := -iquote includes/ -O2 -std=gnu99 -Wall -Wextra
LINKFLAGS := -lm
OUTPUT := out/
SRC := src/

.PHONY := clean

$(OUTPUT)%.o : $(SRC)%.c OUT
	$(CC) $(CFLAGS) -c $< -o $@

dijkstra : $(OUTPUT)dijkstra.o $(OUTPUT)utils.o $(OUTPUT)path.o
	$(CC) $(CFLAGS) $^ -o $@ $(LINKFLAGS)

OUT:
	-mkdir $(OUTPUT)

clean :
	rm -f dijkstra
	rm -f utils
	rm -f $(OUTPUT)*.o
	-rmdir $(OUTPUT)
