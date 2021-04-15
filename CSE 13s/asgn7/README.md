To create the executables, called encode and decode, type in the command "make"
or "make all". To use either executable type in the name of the executable.

The following are the arguments that you may use with the encode executable.
-v	: Display compression statistics
-i	: (input required) Specify input to compress (stdin by default)
-o	: (input required) SPecify output of compressed input (stdout by default)

The following are the arguments that you may use with the decode executable.
-v	: Display decompression statistics
-i	: (input required) Specify input to decompress (stdin by default)
-o	: (input required) SPecify output of decompressed input (stdout by default)

ANY combination of these flags is supported. When youve finished typing in your
executable and flags, hit enter and the program will run.

You may also wish to us valgrind, a programming tool for memory debuffing and leak
detection. To do so just type valgrind before the executable and desired flags.

You can also use infer by typing "make infer" and it will run infer tests. Infer
will give a REASOURCE LEAK error but it must be false because nowhere in my code do
I call exit and everywhere that I return in my main I use close on my open files.

If you wish to remove the object files, the executables, and the infer file that
were creaeted when you typed in make or "make all" you can type in "make clean" and
all of them will be removed.

