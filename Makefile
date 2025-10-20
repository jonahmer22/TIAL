all:
	gcc -Wall -Wextra -I ./include/ -I ./deps/arena/ ./deps/arena/arena.c ./src/*.c -o nal

clean:
	rm ./nal
