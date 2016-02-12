#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {
	if (!str || length < 1) return false; // check parameters
	if (*(str + (length -1)) == '\0') return true; // check that there is a null terminator
	return false; // return false if there isn't
}

char *string_duplicate(const char *str, const size_t length) {
	if (!str || length == 0) { // error check parameters
		return NULL;
	} else {
		return strndup((char *)str, length); // copy the duplicated string
	}

	return NULL; // return null otherwise
}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {	
	if (!str_a || !str_b || length == 0) return false; // error check parameters

	if (strncmp(str_a, str_b, length) == 0) return true; // compare two string to each other

	return false; // return false if they aren't equal
}

int string_length(const char *str, const size_t length) {
	if (!str || length < 1) return 0-1; // error check parameters 
	return strlen(str); // return the string length
}

int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {
	if (!str || !delims || str_length == 0 || tokens == NULL || max_token_length == 0 || requested_tokens == 0) return 0; // error check paramters
	
	// Unused variables: str_length, max_token_length, requested tokens
	// Check that the tokens array has memory allocated at each index
	int i;
	for (i=0; i<requested_tokens;i++) { // check that there is memory at all indicies of token
		if(*(tokens+i) == NULL) return 0-1; // return -1 if one doesn't have memory allocated
	}

	i = 0;
	char *temp = strndup(str, str_length); // copy the string to a new pointer
	char *token_copy = strtok(temp, delims); // tokenize 
	while (token_copy != NULL) { // loop until you get to the end of the string
		strncpy(*(tokens+i), token_copy, max_token_length); // copy the token to the token array
		token_copy = strtok(NULL, delims); // tokenize the next part 
		i++; // increment counter
	}

	return i; // return counter 
}

bool string_to_int(const char *str, int *converted_value) {
	if (!str || converted_value == NULL) return false; // How to check that the string will fit in an int
	*converted_value = strtol(str, NULL, 10); // convert the string to a long
	if (*converted_value >= INT_MAX) { // if the long is larger than the maximum int size 
		*converted_value = 0; // set the int to 0 if it is larger than an int
		return false; // return false if it is not an int
	}
	return true; // return true if it is an int
}
