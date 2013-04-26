#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	int childpid;
	char *argv[] = {"/bin/ls", "-al", NULL };

	childpid = fork();

	if (childpid) {
		int ret;

		ret = execv("/bin/ls", argv);

		if (ret) {
			printf("%d\n", ret);
		}
		exit(0);
	} else {
		wait();
	}
	return 0;
}
