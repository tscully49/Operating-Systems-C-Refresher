#include "../include/debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// protected function, that only this .c can use
int comparator_func(const void *a, const void *b) {
    return *(uint8_t *)a - *(uint8_t *)b; // Function that I did not write 
}

bool terrible_sort(uint16_t *data_array, const size_t value_count) {
    if (!data_array || value_count < 1) return false; // Error checking on parameters

    uint16_t *sorting_array = (uint16_t *)malloc(value_count * sizeof(uint16_t)); // malloc memory for a new array
    for (int i = 0; i < value_count; ++i) { // Copt the data array into a new array
        sorting_array[i] = data_array[i]; // copy values 
    }

    qsort(sorting_array, value_count, sizeof(uint16_t), comparator_func); // quick sort on the new array

    bool sorted = true; // set value to true 
    for (int i = 0; i < value_count-1; ++i) { // check that the array is sorted 
        sorted &= sorting_array[i] <= sorting_array[i + 1]; 
    }

    if (sorted) { // if true 
        memcpy(data_array,sorting_array, value_count*sizeof(uint16_t)); // copy the sorting array into data array 
    }

    free(sorting_array);

    return sorted; // return true/false 
}

