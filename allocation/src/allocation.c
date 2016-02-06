#include "../include/allocation.h"

void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
	if (member_size < 1 || nmember < 1) return NULL;
	if (clear == 0) {
		void *pointer = malloc(member_size*nmember);
		if (pointer == NULL) return NULL;
		return pointer;
	} else {
		void *pointer = calloc(nmember, member_size);
		if (pointer == NULL) return NULL;
		return pointer;
	}
}

void* reallocate_array(void* ptr, size_t size)
{
	if (!ptr) return NULL;
	if (size == SIZE_MAX) free(ptr);
	void *pointer = realloc(ptr, size);
	if (pointer == NULL) return NULL;

	return pointer;
}

void deallocate_array(void** ptr)
{
	if (!ptr) return;
	free(*ptr);
	*ptr = NULL;
}

char* read_line_to_buffer(char* filename)
{	
	if (!filename) return NULL;
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) return NULL;

	size_t c, count;

    count = 0;
    while (1) {
        c = fgetc(fp);
        if(c == EOF || c == '\n') break;
        ++count;
    }
	rewind(fp);

	char *string = (char*)allocate_array(sizeof(char), count+1, 0);

	if (string == NULL) return NULL;

	size_t check = fread(string, count, 1, fp);

	if (check < 1) return NULL;

	fclose(fp);
	string[count] = 0;
	return string;
}
