CC := g++
CFLAGS := -iquote ./headers -Wall -Wextra -std=c++11 -O1
SRC := $(wildcard src/*.c)
SRCS := $(SRC) main.c
.PHONY: clean

main: $(SRCS:%.c=%.o)
	$(CC) $(CFLAGS) -o $@ $^

lib:
	ar -cvq libpath.a $(SRC:%.c=%.o)

clean:
	rm -f $(SRCS:%.c=%.o)
	rm -f main
