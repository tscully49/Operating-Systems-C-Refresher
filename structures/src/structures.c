
#include "../include/structures.h"

int compare_structs(sample_t* a, sample_t* b)
{
	if (a->a == b->a && a->b == b->b && a->c == b->c) return 1; // return 1 if all parts of the data structure are equal
	return 0; // return 0 otherwise
}

void print_alignments()
{
	printf("Alignment of int is %zu bytes\n",__alignof__(int));
	printf("Alignment of double is %zu bytes\n",__alignof__(double));
	printf("Alignment of float is %zu bytes\n",__alignof__(float));
	printf("Alignment of char is %zu bytes\n",__alignof__(char));
	printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
	printf("Alignment of short is %zu bytes\n",__alignof__(short));
	printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}

int sort_fruit(const fruit_t* a,int* apples,int* oranges, const size_t size)
{
	if (!a || apples < 0 || oranges < 0 || size < 1) return -1; // error check params
	int i;
	for (i=0;i<size;++i) { // loop through the fruits array
		if (a[i].type == 1) { // check if the type is an apple
			*apples = *apples + 1; // increment apples
		} else if (a[i].type == 2) { // if it is an orange
			*oranges = *oranges + 1; // increment oranges
		}
	}
	return i; // return the total number of fruits
}

int initialize_array(fruit_t* a, int apples, int oranges)
{
	if (!a || apples < 0 || oranges < 0) return -1; // error check parameters
	int i,j,k=0;
	for (i=0;i<apples;++i) { // add all apples to fruits array
		a[k].type = 1; // type 1 == apple
		k++; // increment total number of fruits
	}
	for (j=0;j<oranges;++j) { // add all oranges to fruits array
		a[k].type = 2; // type 2 == orange
		k++; // increment number of fruits
	}
	return 0; // return 0
}

int initialize_orange(orange_t* a)
{	
	if (!a) return -1; // error check
	a->type = 2; // type 2 == orange
	a->weight = 43; // random value
	a->peeled = 1; // random value
	return 0;
}

int initialize_apple(apple_t* a)
{	
	if (!a) return -1; // error check
	a->type = 1; // type 1 == apple
	a->weight = 5; // random value
	a->worms = 4; // random value
	return 0;
}

/*
typedef struct orange
{
	int type;
	int weight;
	short peeled;
}orange_t;

typedef struct apple
{
	int type;
	int weight;
	int worms;
}apple_t;

typedef struct fruit
{
	int type;
	char padding[8];
}fruit_t;
*/
