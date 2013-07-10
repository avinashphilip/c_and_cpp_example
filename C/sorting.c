#include <stdio.h>
#include "sort.h"

int main()
{
	int array[] = {4,3,2,1};
	int i;

	bubble_sorting_int(array, sizeof(array)/sizeof(array[0]), ascending);

	for (i=0; i < sizeof(array)/sizeof(array[0]); i++)
		printf("%d\n", array[i]);

	insertion_sorting_int(array, sizeof(array)/sizeof(array[0]), descending);

	for (i=0; i < sizeof(array)/sizeof(array[0]); i++)
		printf("%d\n", array[i]);
	return 0;
}
