#include <stdio.h>

int main()
{
	int i = 0;
	do {
		i++;
		printf("%d\n", i);

		if (i == 1)
			continue;

		i++;
	} while (i++ == 1);
	return 0;
}

