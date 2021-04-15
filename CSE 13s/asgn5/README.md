To create the executable, sorting, type in the command "make" or "make all".
To use the sorting executable type in sorting. This executable works on its
own and also with the following arguments.
-A	This will print out the results of all sorting methods. This is the
	default argmument if no other sorting methods are specified.
-b	This will print out the results of bubble sort.
-s	This will print out the results of shell sort.
-q	This will print out the results of quick sort.
-i	This will print out the results of binary insertion sort.
-p	This, followed by an integer value, specifies the first number of 
	elements to be printed from the sorted array. Defaults to 100.
-r	This, followed by an integer vaule, specifies the seed for the 
	random number generator that creates the unsorted array. Defaults
	to 8222022.
-n	This, followed by an integer value, specifies the length of the
	array to be sorted. Defaults to 100.

When you've finished typing in your executable command and any desired 
arguments, hit enter and the executable will print out the desired output.

You may also wish to use valgrind, a programing tool for memory debugging and
leak detection. To do so just type valgrind before the executable command and
any additional arguments. Or you may also just type 'make valgrind'.

You can also use infer by typing 'make infer' and it will run infer tests.

