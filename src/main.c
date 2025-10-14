#include "main.h"
#include "arena.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

char *readFile(const char *path, size_t *outLen){
	FILE *file = fopen(path, "rb");	// rb means read as binary so I get all bytes
	if(!file)
		return NULL;
	
	// check whether the arena has been initialized
	if(!arenaIsInitialized()){
		fprintf(stderr, "[FATAL]: Arena did not initialize.\n");

		exit(10);
	}

	// get the file size in bytes
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocate the char buffer size
	char *buffer = arenaAlloc(sizeof(char) * size + 1);	// add one for EOF
	if(!buffer){
		fclose(file);
	
		return NULL;
	}
	
	// read the file into the buffer
	if(fread(buffer, 1, size, file) != (size_t)size){
		fclose(file);
		
		return NULL;
	}

	buffer[size] = '\0';	// add back EOF
	if(outLen)	// if we want the size back
		*outLen = (size_t)size;

	return buffer;
}

int main(int argc, char **argv){
	// get user input
	// at this stage it should only be an input file
	if(argc < 2 || argc >= 3){
		fprintf(stderr, "Usage: ./a-lang <./path/to/file>\n");

		return 1;
	}

	// initialize the arena that'll hold the source and long lasting objects
	arenaInit();

	// initialize variables for getting the source buffer
	size_t length = 0;
	char *buffer = NULL;

	// get the source buffer
	buffer = readFile(argv[argc - 1], &length);
	if(!buffer){
		fprintf(stderr, "[FATAL]: Could not load file buffer.\n");
		arenaDestroy();

		return 2;
	}

	// just for testing prints the file and it's length
	printf("%s\n%s contains %ld Bytes\n", buffer, argv[argc - 1], length);

	// cleanup
	arenaDestroy();

	return 0;
}
