all:
	gcc -Wall -Wextra -I ./include/ ./src/*.c -o a-lang

clean:
	rm ./a-lang
