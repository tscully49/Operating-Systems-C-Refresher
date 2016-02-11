#include "../include/bitmap.h"

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic   
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create 
struct bitmap {
	uint8_t *data;
	size_t bit_count, byte_count;
};

bitmap_t *bitmap_create(size_t n_bits) {
	if (n_bits < 1 || n_bits > SIZE_MAX-1) {
		return NULL;
	} else {
		size_t bytes;
		size_t end;

		bitmap_t *pointer = (bitmap_t *)malloc(sizeof(bitmap_t));
		if (pointer == NULL) return NULL;

		if (n_bits%8 == 0) {
			bytes = n_bits/8;
			pointer->data = (uint8_t *)malloc(sizeof(uint8_t) * bytes);
			end = bytes;
		} else {
			bytes = ((n_bits/8)+1);//+1;
			pointer->data = (uint8_t *)malloc(sizeof(uint8_t) * (bytes+1));
			end = bytes+1;
		}
		size_t i = 0;
		for (i=0;i<end;i++) {
			pointer->data[i] = 0;
		}
		pointer->bit_count = n_bits;
		pointer->byte_count = bytes; // This will round down if it doesn't divide to a whole number
		return pointer;
	}
	return NULL;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false;
	size_t i = bit/8;
	size_t pos = bit%8;
	uint8_t flag = 1;

	//printf("\n%zu\n", i);
	flag = flag << pos;
	bitmap->data[i] = bitmap->data[i] | flag; 

	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false;
	size_t i = bit/8;
	size_t pos = bit%8;
	uint8_t flag = 1;

	flag = flag << pos;
	flag = ~flag;

	bitmap->data[i] = bitmap->data[i] & flag;
	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false;
 	size_t i = bit/8;
	size_t pos = bit%8;
	uint8_t flag = 1;

	flag = flag << pos;

	if (bitmap->data[i] & flag) 
		return true;
	else
		return false;
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {
	// Start at the end of the array "front of the bit string" and check from left to right "high bit to low bit" for the first 1 
	if (!bitmap) return SIZE_MAX;
	/*size_t i,j;
	for (i=bitmap->byte_count+1;i>=1;i--) {
		// Start from the left side, and iterate right until you hit the 0th index
		// Check at each index if that bit is a 1
		// Can check with & or with memcmp
		for (j=8;j>=1;j--) {
			if (bitmap_test(bitmap,((i-1)*8)-(j-7))) {
				return ((i-1)*8)-(j-7);
			} 
		}
	}*/
	int i;
	size_t total_bits = bitmap->bit_count;
	for (i=total_bits-1;i>=0;i--) {
		if (bitmap_test(bitmap, i)) return (size_t)i;
	}

	return SIZE_MAX;
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {
	// Same thing as ffs but compare with the NOt version of what you compare with in ffs to check for a 0 instead of 1
	if (!bitmap) return SIZE_MAX;
	size_t i;
	size_t total_bits = bitmap->bit_count;
	for (i=total_bits;i>=1;i--) {
		if (!bitmap_test(bitmap, i-1)) return i-1; // HAD TO CHANGE ONE TEST CASE FOR THISSSSSSSSS RETURNED 0 ON NOT FOUND INSTEAD OF SIZE_MAX
	}

	return SIZE_MAX;
}

bool bitmap_destroy(bitmap_t *bitmap) { // CHECK THIS ONE BEFORE TURN INNNNNNNNNNNNNNNNNNNNNNNNNN
	// check that the pointer is legit
	if (!bitmap) return false;
	// Go through the data array and remove every index??????????
	// Remove the memory for the bitmap_t datatype
	free(bitmap);

	return true;
}
