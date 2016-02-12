#include "../include/allocation.h"

void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
	if (member_size < 1 || nmember < 1) return NULL; // Error checking on parameters 
	if (clear == 0) { // check if the clear flag is set or not 
		void *pointer = malloc(member_size*nmember); // if flag is not set, memory will be malloced, not initialized
		if (pointer == NULL) return NULL; // if the allocation failed, return null
		return pointer; // return the pointer otherwise
	} else {
		void *pointer = calloc(nmember, member_size); // if flag is set, memory will be initialized and malloced with calloc
		if (pointer == NULL) return NULL; // if the allocation failed, return null
		return pointer; // return the pointer otherwise 
	}
}

void* reallocate_array(void* ptr, size_t size)
{
	if (!ptr || size < 1 || size == SIZE_MAX) return NULL; // error checking parameters
	if (size == SIZE_MAX) free(ptr); // if the size is negative, free memory
	void *pointer = realloc(ptr, size); // otherwise, realloc the memory to the size parameter
	if (pointer == NULL) return NULL; // if the new memory allocation failed, return null

	return pointer; // otherwise return the pointer
}

void deallocate_array(void** ptr)
{
	if (!ptr) return; // error check parameters
	free(*ptr); // free memory
	*ptr = NULL; // set the pointer equal to null after memory was freed 
	return;
}

char* read_line_to_buffer(char* filename)
{	
	if (!filename) return NULL; // error check parameters
	FILE *fp = fopen(filename, "rb"); // open the file with reading and binary
	if (fp == NULL) return NULL; // if the file open fails, return null 

	size_t c, count; //initialize variables

    count = 0; // set count to 0
    while (1) { 
        c = fgetc(fp); // get a character of the file
        if(c == EOF || c == '\n') break; // stop if you get to a new line or the end of file
        ++count; // count number of characters in the line 
    }
	rewind(fp); // rewind the file pointer 

	char *string = (char*)allocate_array(sizeof(char), count+1, 0); // create memory for an array of characters in the first line of the file

	if (string == NULL) return NULL; // if the character array allocation failed, the return null

	size_t check = fread(string, count, 1, fp); // read the first line of the file to the character array allocated

	if (check < 1) return NULL; // if nothing was read from the file, return null

	fclose(fp); // close the file pointer
	string[count] = 0; // set the end of the string to the null terminator
	return string; // return the array
}
