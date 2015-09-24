all: fsdemo netdemo sockpairdemo

FLAGS:=-std=c99 -Wall -Wextra -Wshadow -pedantic -O

fsdemo:
	gcc $(FLAGS) fsserver.c -o fsserver.out
	gcc $(FLAGS) fsclient.c -o fsclient.out

netdemo:
	gcc $(FLAGS) netserver.c -o netserver.out
	gcc $(FLAGS) netclient.c -o netclient.out

sockpairdemo:
	gcc $(FLAGS) sockpair.c -o sockpair.out
clean:
	 rm -f *.out *~
