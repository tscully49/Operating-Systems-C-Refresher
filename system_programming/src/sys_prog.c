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
	if (!input_filename || !dst || offset > dst_size || dst_size < 1) return false; // error check parameters
	if(strcmp(input_filename, "\n")==0 || strcmp(input_filename, "\0") == 0 || strcmp(input_filename, "") == 0) return false; // error check filenames 
	int fd = open(input_filename, O_RDONLY); // open file with read only
	if (fd == -1) {  // if file didn't open properly return false
		return false; 
	} else {
		lseek(fd, offset, SEEK_SET); // move to the part of the file that should be read
		if (read(fd, dst, dst_size) == dst_size) { // read from the file and check that it reads the right ammount
			if (close(fd) != -1) return true; // return true after proper file close
		}
	}

	return false;
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size) {
	if (!src || !output_filename || src_size < 1) return false; // error check parameters
	if(strcmp(output_filename, "\n")==0 || strcmp(output_filename, "\0") == 0 || strcmp(output_filename, "") == 0) return false; // error check file names
	int fd = open(output_filename, O_CREAT | O_TRUNC | O_WRONLY); // open file, create it, truncate it, and open for write only
	if (fd == -1) { // if the file didn't open properly
		return false;
	} else {
		printf("\nOPEN\n");
		lseek(fd, offset, SEEK_SET); // move to the correct part of the file
		if (write(fd, src, src_size) == src_size) { // write to the file and check that it wrote to the file correctly
			if (close(fd) != -1) return true; // close the file 
		}
	}

	return false;
}


bool file_stat(const char *query_filename, struct stat *metadata) {
	if (!query_filename || !metadata) return false; // error check params 
	if (stat(query_filename, metadata) == -1) { // call stat on the params
		return false; // if it didn't work, return -1
	} else {
		return true; // otherwise return true
	}
	return false;
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {
	if (!src_data || !dst_data || src_count == 0) return false; // error check parameters
	int i;
	uint32_t temp,a,b,c,d;
	for (i=0;i<src_count;++i) { //loop through bytes
		a = (src_data[i] & 0x000000ff) << 24u; // shifts last byte to front 
		b = (src_data[i] & 0x0000ff00) << 8u; // shifts 3 byte to the left one
		c = (src_data[i] & 0x00ff0000) >> 8u; // shifts 2nd byte to the right one
		d = (src_data[i] & 0xff000000) >> 24u; // shifts the first byte to the end
		temp = a|b|c|d; // ORs all parts together
		dst_data[i] = temp; // set temp to the dst_data[i]
	}

	return true; // return true
}
