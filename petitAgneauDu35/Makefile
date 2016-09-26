CC := gcc
CFLAGS := -O2 -std=gnu99 -Wall -Wextra
LINKFLAGS := -lm

.PHONY := clean

dijkstra : dijkstra.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LINKFLAGS) 

clean :
	rm -f dijkstra
	rm -f utils
	rm -f *.o
