all: basic sigset

FLAGS:=-Wall -Wextra -Wshadow -pedantic -O

basic:
	gcc -std=c99 $(FLAGS) basic.c -o basic
sigset:
	gcc -std=gnu99 $(FLAGS) sigset.c -o sigset
clean:
	 rm -f *.o basic sigset *~
