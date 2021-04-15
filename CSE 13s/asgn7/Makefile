CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)
E_OBJS = io.o trie.o encode.o
D_OBJS = io.o word.o decode.o
OBJECTS = $(D_OBJS) $(E_OBJS)
EXECBIN = encode decode

.PHONY	: all
all	: $(EXECBIN)

encode	: $(E_OBJS)
	$(CC) $(E_OBJS) -o encode

decode	: $(D_OBJS)
	$(CC) $(D_OBJS) -o decode

encode.o	: encode.c
	$(CC) -c encode.c

decode.o	: decode.c
	$(CC) -c decode.c

trie.o	: trie.c
	$(CC) -c trie.c

word.o	: word.c
	$(CC) -c word.c

io.o	: io.c
	$(CC) -c io.c

.PHONY	: clean
clean	:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out

infer	:
	make clean; infer-capture -- make; infer-analyze -- make

