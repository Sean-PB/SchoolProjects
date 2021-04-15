To create the executable, called hatterspeak, type in the command "make or
"make all". To use the hatterspeak executable type in "hatterspeak". This
executable works on its own and also with the following arguments:
-s	will supress the letter from the censor, and instead print the 
	statistics that were computed.
-h	size specifies that the hash table will have size entries (the 
	default will be 10000). Must be a positive integer.
-f	size specifies that the Bloom filter will have size entries (the
	default will be 2^20). Must be a positive integer.
-m	will use the move-to-front rule.
-b	will not use the move-to-front-rule. This is the default as well.
ANY combination of these flags except for -m -b is supported (if both -m
and -b flags are set then it just uses whichever was set last).

When you've finished typing in your executable and flags, hit enter and the
executable will then allow you to input your message. Once you finish
inputting your message press ctrl + D to indicate that your message is done.
After this the desired output will be printed to the screen.

You may also wish to use valgrind, a programming tool for memory debugging
and leak detection. To do so just type valgrind before the executable and
desired flags. You may also just type "make valgrind".

You can also use infer by typing "make infer" and it will run infer tests.

If you wish to remove the object files, the executable, and the infer file
that were created when you typed in make or "make all" you can type in
"make clean".

