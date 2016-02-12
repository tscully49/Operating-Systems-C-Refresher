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
	if (n_bits < 1 || n_bits > SIZE_MAX-1) { // error check parameters
		return NULL; 
	} else {
		size_t bytes;
		size_t end;

		bitmap_t *pointer = (bitmap_t *)malloc(sizeof(bitmap_t)); // malloc memory for the bytes array
		if (pointer == NULL) return NULL; // if the malloc fails...

		if (n_bits%8 == 0) { // if there are exactly enough bits to fill all bytes 
			bytes = n_bits/8; // set the number of bytes equal to the bumber of bits divided by 8
			pointer->data = (uint8_t *)malloc(sizeof(uint8_t) * bytes); // malloc memory for the bytes
			end = bytes; // sets the variable for the for loop
		} else {
			bytes = ((n_bits/8)+1); // add an extra byte 
			pointer->data = (uint8_t *)malloc(sizeof(uint8_t) * bytes); // malloc memory
			end = bytes+1; // set the for loop variable
		}
		size_t i = 0;
		for (i=0;i<end;i++) { // set all bytes to 0
			pointer->data[i] = 0;
		}
		pointer->bit_count = n_bits; // set number of bits
		pointer->byte_count = bytes; // This will round down if it doesn't divide to a whole number
		return pointer; // return pointer to the bytes
	}
	return NULL;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false; // error check parameters
	size_t i = bit/8; // find which byte the bit is in
	size_t pos = bit%8; // find which bit in the byte to set 
	uint8_t flag = 1; // set the byte = 00000001

	flag = flag << pos; // bit shift left pos number of times
	bitmap->data[i] = bitmap->data[i] | flag; // set the bit in the correct byte

	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false; // error check parameters
	size_t i = bit/8; // find which byte the bit is in 
	size_t pos = bit%8; // find which bit in the byte to reset to 0
	uint8_t flag = 1; // set flag to 00000001

	flag = flag << pos; // left shift pos number of times
	flag = ~flag; // set the 0's to 1's and 1's to 0's "NOT"

	bitmap->data[i] = bitmap->data[i] & flag; // reset the correct bit to 0
	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {
	if (!bitmap || bit > SIZE_MAX-1 || bit > bitmap->bit_count) return false; // error check parameters
 	size_t i = bit/8; // find which byte to check
	size_t pos = bit%8; // find which bit in the byte to check
	uint8_t flag = 1; // set flag to 00000001

	flag = flag << pos; // left shift the bit 

	if (bitmap->data[i] & flag) // compare the byte and the flag
		return true; 
	else
		return false;
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {
	// Start at the end of the array "front of the bit string" and check from left to right "high bit to low bit" for the first 1 
	if (!bitmap) return SIZE_MAX; // error check parameters

	int i;
	size_t total_bits = bitmap->bit_count;
	for (i=total_bits-1;i>=0;i--) { // loops through each bit to see which is the first set bit 
		if (bitmap_test(bitmap, i)) return (size_t)i; // use bitmap_test function to test each bit
	}

	return SIZE_MAX; // return size_max if not found
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {
	// Same thing as ffs but compare with the NOt version of what you compare with in ffs to check for a 0 instead of 1
	if (!bitmap) return SIZE_MAX; // error check params
	size_t i;
	size_t total_bits = bitmap->bit_count;
	for (i=total_bits;i>=1;i--) { // loop through bits to find which is the first that isn't checked
		if (!bitmap_test(bitmap, i-1)) return i-1;
	}

	return SIZE_MAX;
}

bool bitmap_destroy(bitmap_t *bitmap) {
	// check that the pointer is legit
	if (!bitmap) return false;
	// Free data 
	free(bitmap->data);
	// Remove the memory for the bitmap_t datatype
	free(bitmap);

	return true;
}
