#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int pfd[2];
	pid_t cpid;
	char buf;
	fd_set fds;
	struct timeval tv;
	int retval;


	assert(argc == 3);

	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	FD_ZERO(&fds);
	FD_SET(pfd[0], &fds);

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	/* Wait up to five seconds. */
	tv.tv_sec = atoi(argv[2]);
	tv.tv_usec = 0;

	if (cpid == 0) {
		close(pfd[1]); /* Close unused write end */

		/* Child reads from pipe */
		printf("child\n");
		retval = select(pfd[0] + 1, &fds, NULL, NULL, &tv);
		/* Dont rely on the value of tv now! */
		if (retval == -1) {
			perror("select()");
		} else if (retval) {
			printf("Data is available now.\n");
			while(read(pfd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
			/* FD_ISSET(0, &rfds) will be true. */
		} else {
			printf("No data within %s seconds.\n", argv[2]);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(pfd[0]);
		_exit(EXIT_SUCCESS);
	} else { /* Parent writes argv[1] to pipe */
		close(pfd[0]); /* Close unused read end */

		printf("Parent\n");
		getchar();
		write(pfd[1], argv[1], strlen(argv[1]));
		close(pfd[1]); /* Reader will see EOF */
		wait(NULL); /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
