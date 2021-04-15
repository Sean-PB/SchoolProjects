CFLAGS=-Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)
OBJECTS = tower.o stack.o
EXECBIN = tower

.PHONY	: all
all	: $(EXECBIN)

$(EXECBIN)	: tower.o stack.o
	$(CC) $(OBJECTS) -o $(EXECBIN)

tower.o	: tower.c
	$(CC) -c tower.c

stack.o	: stack.c
	$(CC) -c stack.c

.PHONY	: clean
clean	:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
