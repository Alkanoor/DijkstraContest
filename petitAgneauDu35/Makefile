CC := gcc
CFLAGS := -O2 -std=gnu99 -Wall -Wextra -lm
.PHONY := clean 

dijkstra : dijkstra.o utils.o
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -f dijkstra
	rm -f utils
	rm -f *.o
