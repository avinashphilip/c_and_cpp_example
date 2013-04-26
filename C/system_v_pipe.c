#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <sys/types.h>
int main()
{
	int fd[2], nbytes;
	pid_t childpid;
	char string[] = "Hello, parent.!\n";
	char readbuffer[80];
	struct pollfd fds[1];
	nfds_t nfds = 1;

	pipe(fd);
	fds[0].fd = fd[0];
	fds[0].events = POLLIN | POLLPRI;

	if ((childpid = fork()) == -1) {
		perror("fork");
		exit(-1);
	}

	if(childpid == 0) {
		printf("child process executing\n");
		/* Child process closes up input side of pipe */
		close(fd[0]);
		printf("child goes to sleep\n");
		sleep(5);
		/* Send "string" through the output side of pipe */
		write(fd[1], string, (strlen(string)+1));
		exit(0);
	} else {
		int ret;

		/* Parent process closes up output side of pipe */
		printf("parent process executing\n");
		close(fd[1]);

		printf("parent process polling indefinite time\n");
		ret = poll(fds, nfds, -1);
		if (ret == -1) {
			perror ("poll");
			exit(EXIT_FAILURE);
		}
		printf("Parent process poll completed %d %x\n", ret, fds[0].revents);
		/* Read in a string from the pipe */
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s", readbuffer);
		//wait();
	}

	return 0;
}
