#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;
	struct pollfd poll_fd;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    /* Child reads from pipe */
		close(pipefd[1]);          /* Close unused write end */

		poll_fd.fd = pipefd[0];
		poll_fd.events = POLLIN;
		if (poll(&poll_fd, 1, 6000)) {
			while (read(pipefd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
		} else {
			perror("Timeout occured on read pipe\n");
		}

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	} else {            /* Parent writes argv[1] to pipe */
		close(pipefd[0]);          /* Close unused read end */

		getchar();
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
