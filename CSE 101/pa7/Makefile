#------------------------------------------------------------------------------
#  Sean Brandon, spbrando
#  CSE 101, Spring 2021
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                  makes Order
#  make WordFrequency    makes WordFrequency
#  make clean            removes all binaries
#  make check1           checks WordFrequency for memory leaks on Big.txt
#  make check2           checks Order for memory leaks on English.txt
#------------------------------------------------------------------------------

TOP              = Order
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = WordFrequency
TEST2            = DictionaryTest
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
TEST_OBJ2        = $(TEST2).o
TEST_SRC2        = $(TEST2).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)

$(TEST) : $(TEST_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

$(TEST2) : $(TEST_OBJ2) $(ADT_OBJ)
	$(LINK) $(TEST2) $(TEST_OBJ2) $(ADT_OBJ)

$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)

$(TEST_OBJ) : $(TEST_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC)

$(TEST_OBJ2) : $(TEST_SRC2) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC2)

$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST2) $(TEST_OBJ) $(TEST_OBJ2) $(ADT_OBJ) junk

check1 : $(TEST)
	$(MEMCHECK) $(TEST) Big.txt junk

check2 : $(TOP)
	$(MEMCHECK) $(TOP) English.txt junk

check3 : $(TEST2)
	$(MEMCHECK) $(TEST2)
