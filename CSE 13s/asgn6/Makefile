CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99
CC=clang $(CFLAGS)
OBJECTS = hatterspeak.o speck.o bv.o bf.o ll.o hatspeak.o hash.o parser.o
EXECBIN = hatterspeak

.PHONY	: all
all	: $(EXECBIN)

$(EXECBIN)	: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)

hatterspeak.o	: hatterspeak.c
	$(CC) -c hatterspeak.c

speck.o	: speck.c
	$(CC) -c speck.c

bv.o	: bv.c
	$(CC) -c bv.c

bf.o	: bf.c
	$(CC) -c bf.c

ll.o	: ll.c
	$(CC) -c ll.c

hatspeak.o	: hatspeak.c
	$(CC) -c hatspeak.c

hash.o	: hash.c
	$(CC) -c hash.c

parser.o	: parser.c
	$(CC) -c parser.c

.PHONY	: clean
clean	:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out

infer	:
	make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
	make all
	valgrind hatterspeak
