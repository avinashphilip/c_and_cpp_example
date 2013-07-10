#include <stdio.h>
/**
 * C diid n't support default arguments, but compile it
 * with g++ will work.
 * It is supported only in C++
 */
void find(int arg = 0)
{
	printf("arg %d\n",arg);
}

int main()
{
	find(3);
	find();
	return 0;
}
