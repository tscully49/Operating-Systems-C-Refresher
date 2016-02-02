#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) {
	if (!src || !dst || elem_size == 0 || elem_count == 0) {
  		return false;
	}
	if (memcpy(dst, src, elem_size * elem_count) != NULL) {
		return true;
	}

	return false;
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) {
	if (!data_one || !data_two || elem_size == 0 || elem_count == 0) {
		return false;
	}

	if (memcmp(data_one, data_two, elem_size * elem_count) == 0) {
		return true;
	}

	return false;
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) { 
	if (!data || !target || elem_size == 0 || elem_count == 0) {
		return 0-1;
	}

	int i;
	const char *new_data = (char *)data;

	for (i=0;i<elem_count;i++) {
		if (memcmp((new_data + (i*elem_size)), target, elem_size) == 0) {
			return i;
		}
	}

	return 0-1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {
	if (!src_data || !dst_file || elem_size == 0 || elem_count == 0) {
		return false;
	}

	if (strcmp(dst_file, "") == 0 || strcmp(dst_file, "\n") == 0) return false;

	FILE *fp;
	if ((fp = fopen(dst_file , "wb")) != NULL) {
		if (fwrite((const char *)src_data, 1, (elem_count*elem_size), fp) != elem_size*elem_count) return false;
		fclose(fp);
		return true;
	}

	return false;
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {
	if (!src_file || !dst_data || elem_size == 0 || elem_count == 0) {
		return false;
	}

	FILE *fp;
	if ((fp = fopen(src_file , "rb")) == NULL)
		return false;

	if (strcmp(src_file, "") != 0 && strcmp(src_file, "\n") != 0) {
		fread(dst_data, elem_size, elem_count, fp);
		char *dst_data = dst_data;
		return true;
	}
	fclose(fp);

	return false;
}
