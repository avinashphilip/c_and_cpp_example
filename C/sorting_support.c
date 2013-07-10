#include "sort.h"

inline void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sorting_int(int *array, int size, enum sort_type type)
{
	int i, j;

	for (i = 0; i < size - 1; i++) {
		for (j=0; j< (size -1 - i); j++) {

			if (type == ascending) {
				if (array[j] > array[j+1])
					swap(&array[j], &array[j+1]);
			} else {
				if (array[j] < array[j+1])
					swap(&array[j], &array[j+1]);
			}
		}
	}
}

void insertion_sorting_int(int *array, int size, enum sort_type type)
{
	int i, j, tmp;

	for (i=0; i < size -1; i++) {
		for(j=i; j < size; j++) {
			if (type == ascending) {
				if (array[i] > array[j])
					swap(&array[j], &array[i]);
			} else {
				if (array[i] < array[j])
					swap(&array[j], &array[i]);
				
			}
		}
	}
}
