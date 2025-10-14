all:
	gcc -Wall -Wextra -I ./include/ -I ./deps/arena/ ./deps/arena/arena.c ./src/*.c -o a-lang

clean:
	rm ./a-lang
