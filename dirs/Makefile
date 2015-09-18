all: dirs

FLAGS:=-Wall -Wunreachable-code -Wextra -Wshadow -pedantic -O

dirs:
	gcc -std=c99 $(FLAGS) dirs.c -o dirs
clean:
	 rm -f *.o dirs *~
