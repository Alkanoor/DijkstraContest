CC := g++
CFLAGS := -iquote ./headers -Wall -Wextra -std=c++11 -O1
SRC := $(wildcard src/*.c)
.PHONY: clean

main: $(SRC:%.c=%.o)
	$(CC) $(CFLAGS) -o $@ $^

lib:
	ar -cvq libpath.a $(SRC:%.c=%.o)

clean:
	rm -f $(SRC:%.c=%.o)
	rm -f main
