#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) {
	if (!src || !dst || elem_size == 0 || elem_count == 0) { // error check parameters
  		return false;
	}
	if (memcpy(dst, src, elem_size * elem_count) != NULL) { // check that the memcpy worked correctly
		return true; // return true if it did 
	}

	return false; // otherwise return false
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) {
	if (!data_one || !data_two || elem_size == 0 || elem_count == 0) { // error check parameters
		return false;
	}

	if (memcmp(data_one, data_two, elem_size * elem_count) == 0) { // memcmp checks that the two passed parameters are equal
		return true; // return true if they are 
	}

	return false; // otherwise return false
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) { 
	if (!data || !target || elem_size == 0 || elem_count == 0) { // error check parameters
		return 0-1;
	}

	int i;
	const char *new_data = (char *)data; // typecase data to a character pointer

	for (i=0;i<elem_count;i++) { // loop through the array to try and find the character in the array 
		if (memcmp((new_data + (i*elem_size)), target, elem_size) == 0) { // check to see if the index has the value we are looking for
			return i; // return the index
		}
	}

	return 0-1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {
	if (!src_data || !dst_file || elem_size == 0 || elem_count == 0) { // error check parameters
		return false;
	}

	if (strcmp(dst_file, "") == 0 || strcmp(dst_file, "\n") == 0) return false; // more error checking on the dst_file to make sure it isn't a new line or empty string

	FILE *fp;
	if ((fp = fopen(dst_file , "wb")) != NULL) { // open the file to write and in binary
		if (fwrite((const char *)src_data, 1, (elem_count*elem_size), fp) != elem_size*elem_count) return false; // write to file
		fclose(fp); // close file pointer
		return true; // return true if it worked 
	}

	return false;
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {
	if (!src_file || !dst_data || elem_size == 0 || elem_count == 0) { // error check parameters
		return false;
	}

	FILE *fp;
	if ((fp = fopen(src_file , "rb")) == NULL) // open the file for reading and binary
		return false; // return false if it fails 

	if (strcmp(src_file, "") != 0 && strcmp(src_file, "\n") != 0) { // check if the src_file is a new line or empty string
		fread(dst_data, elem_size, elem_count, fp); // read from the file
		char *dst_data = dst_data; // set the pointer equal to the data from the file 
		return true; 
	}
	fclose(fp); // close the file pointer

	return false;
}
