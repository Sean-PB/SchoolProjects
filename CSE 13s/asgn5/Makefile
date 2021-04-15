CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99
CC=clang $(CFLAGS)
OBJECTS = sorting.o bubble.o shell.o quick.o binary.o
EXECBIN = sorting

.PHONY	: all
all	: $(EXECBIN)

$(EXECBIN)	: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)

sorting.o	: sorting.c
	$(CC) -c sorting.c

bubble.o	: bubble.c
	$(CC) -c bubble.c

shell.o	: shell.c
	$(CC) -c shell.c

quick.o	: quick.c
	$(CC) -c quick.c

binary.o	: binary.c
	$(CC) -c binary.c

.PHONY	: clean
clean	:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
	make all
	valgrind sorting
