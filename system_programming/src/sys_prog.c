#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size) {	
	if (!input_filename || !dst || offset > dst_size || dst_size < 1) return false;
	int fd = open(input_filename, O_RDONLY);
	if (fd == -1) { 
		return false; 
	} else {
		lseek(fd, offset, SEEK_SET);
		if (read(fd, dst, dst_size) == dst_size) {
			if (close(fd) != -1) return true;
		}
	}

	return false;
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size) {
	if (!src || !output_filename || src_size < 1) return false;
	int fd = open(output_filename, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1) {
		return false;
	} else {
		lseek(fd, offset, SEEK_SET);
		if (write(fd, src, src_size) == src_size) {
			if (close(fd) != -1) return true;
		}
	}

	return false;
}


bool file_stat(const char *query_filename, struct stat *metadata) {
	if (!query_filename || !metadata) return false;
	if (stat(query_filename, metadata) == -1) {
		return false;
	} else {
		return true;
	}
	return false;
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {
	if (!src_data || !dst_data || src_count == 0) return false;
	int i;
	uint32_t temp,a,b,c,d;
	for (i=0;i<src_count;++i) {
		a = (src_data[i] & 0x000000ff) << 24u; // shifts last byte to front 
		b = (src_data[i] & 0x0000ff00) << 8u; // shifts 3 byte to the left one
		c = (src_data[i] & 0x00ff0000) >> 8u; // shifts 2nd byte to the right one
		d = (src_data[i] & 0xff000000) >> 24u; // shifts the first byte to the end
		temp = a|b|c|d;
		dst_data[i] = temp;
	}

	return true;
}
