CFLAGS=-Wextra -Werror -pedantic
CC=clang $(CFLAGS)
OBJECTS	= sequence.o bv.o sieve.o
EXECBIN	= sequence

.PHONY	: all
all	: $(EXECBIN)

$(EXECBIN)	: $(OBJECTS)
	$(CC) $(OBJECTS) -lm -o $(EXECBIN)

sequence.o	: sequence.c
	$(CC) -c sequence.c

bv.o	: bv.c
	$(CC) -c bv.c

sieve.o	: sieve.c
	$(CC) -c sieve.c

.PHONY	: clean
clean	:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
