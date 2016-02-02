#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {
	if (!str || length < 1) return false;
	if (*(str + (length -1)) == '\0') return true;
	return false;
}

char *string_duplicate(const char *str, const size_t length) {
	if (!str || length == 0) {
		return NULL;
	} else {
		return strndup((char *)str, length);
	}

	return NULL;
}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {	
	if (!str_a || !str_b || length == 0) return false;

	if (strncmp(str_a, str_b, length) == 0) return true;

	return false;
}

int string_length(const char *str, const size_t length) {
	if (!str || length < 1) return 0-1; // This is wrong in the test file 
	return strlen(str);
}

int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {
	if (!str || !delims || str_length == 0 || tokens == NULL || max_token_length == 0 || requested_tokens == 0) return 0;
	
	// Unused variables: str_length, max_token_length, requested tokens
	// Check that the tokens array has memory allocated at each index
	int i;
	for (i=0; i<requested_tokens;i++) {
		if(*(tokens+i) == NULL) return 0-1;
	}

	i = 0;
	char *temp = strndup(str, str_length);
	char *token_copy = strtok(temp, delims); // Producing seg fault
	while (token_copy != NULL) {
		strncpy(*(tokens+i), token_copy, max_token_length);
		token_copy = strtok(NULL, delims);
		i++;
	}

	return i;
}

bool string_to_int(const char *str, int *converted_value) {
	if (!str || converted_value == NULL) return false; // How to check that the string will fit in an int
	*converted_value = strtol(str, NULL, 10);
	if (*converted_value >= INT_MAX) {
		*converted_value = 0;
		return false;
	}
	return true;
}
