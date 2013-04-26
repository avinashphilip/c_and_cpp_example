#include <stdio.h>
int main()
{
	char *arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char **p;

	p = &arr;

	printf("%d\n", *(p + 1));
	return 0;
}
