all: dirs

FLAGS:=-Wall -Wunreachable-code -Wextra -Wshadow -pedantic -O

dirs:
	gcc -std=gnu99 $(FLAGS) daemon.c -o daemon
clean:
	 rm -f *.o dirs *~
