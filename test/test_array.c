#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "../array.h"

int cmp_int(const int *pa, const int *pb)
{
	return *pa - *pb;
}

void assert_in_order(Array *arr)
{
	for (size_t i = 1; i < arr->siz; i++)
		assert(((int *) arr->ptr)[i - 1] <= ((int *) arr->ptr)[i]);
}

void dump(Array *arr)
{
	for (size_t i = 0; i < arr->siz; i++) {
		printf("%d", ((int *) arr->ptr)[i]);

		if (i != arr->siz - 1)
			printf(",");
	}
}

int main()
{
	int i;
	Array arr, arr2;
	srand(time(0));

	printf("testing ini\n");
	array_ini(&arr, sizeof(int), 0, NULL);

	printf("testing add\n");
	i = 1; array_add(&arr, &i);
	i = 3; array_add(&arr, &i);
	i = 4; array_add(&arr, &i);

	printf("testing put\n");
	i = 2; array_put(&arr, &i, 1);
	i = 5; array_put(&arr, &i, arr.siz);

	printf("testing siz: exp: 5 got: %lu\n", arr.siz);
	assert(arr.siz == 5);

	printf("testing cap: exp: 5 got: %lu\n", arr.cap);
	assert(arr.cap == 5);

	printf("testing contents: exp: 1,2,3,4,5 got: "); dump(&arr); printf("\n");
	for (size_t j = 0; j < arr.siz; j++)
		assert((size_t) ((int *) arr.ptr)[j] == j + 1);

	printf("testing cln\n");
	array_cln(&arr2, &arr);

	printf("testing equality: exp: "); dump(&arr); printf(" got: "); dump(&arr2);
	printf("\n");

	for (size_t j = 0; j < arr.siz; j++)
		assert(((int *) arr.ptr)[j] == ((int *) arr2.ptr)[j]);

	printf("testing del\n");
	array_del(&arr);
	array_del(&arr2);

	printf("testing ini after del\n");
	array_ini(&arr, sizeof(int), 5, (void *) &cmp_int);

	printf("testing cap: exp: 0 got: %lu\n", arr.cap);
	assert(arr.cap == 0);

	printf("testing overallocation\n");
	i = 50; array_add(&arr, &i);

	printf("testing cap: exp: 0 got: %lu\n", arr.cap);
	assert(arr.siz == 1);

	printf("testing cap: exp: 6 got: %lu\n", arr.cap);
	assert(arr.cap == 6);

	for (int j = 0; j < 7; j++) {
		i = rand() % 100; array_add(&arr, &i);
	}

	printf("testing siz: exp: 8 got: %lu\n", arr.cap);
	assert(arr.siz == 8);

	printf("testing cap: exp: 12 got: %lu\n", arr.cap);
	assert(arr.cap == 12);

	printf("testing grw\n");
	array_grw(&arr, 5);

	printf("testing siz: exp: 13 got: %lu\n", arr.cap);
	assert(arr.siz == 13);

	printf("testing cap: exp: 18 got: %lu\n", arr.cap);
	assert(arr.cap == 18);

	printf("testing shr\n");
	array_shr(&arr, 5);

	printf("testing siz: exp: 8 got: %lu\n", arr.cap);
	assert(arr.siz == 8);

	printf("testing cap: exp: 8 got: %lu\n", arr.cap);
	assert(arr.cap == 8);

	printf("testing srt\n");
	array_srt(&arr);

	printf("testing order: exp: (sorted) got: "); dump(&arr); printf("\n");
	assert_in_order(&arr);

	for (size_t j = 0; j < arr.siz; j++) {
		i = ((int *) arr.ptr)[j]; ssize_t s = array_fnd(&arr, &i, NULL);

		printf("testing fnd at index %lu: exp: >=0 got: %ld\n", j, s);
		assert(s >= 0);

		int k = ((int *) arr.ptr)[s];

		printf("testing fnd at index %lu: exp: %d got: %d\n", j, i, k);
		assert(k == i);
	}

	printf("testing ins\n");
	for (int j = 0; j < 10; j++) {
		i = rand() % 100; array_ins(&arr, &i);
	}

	printf("testing order: exp: (sorted) got: "); dump(&arr); printf("\n");
	assert_in_order(&arr);

	array_del(&arr);
}
