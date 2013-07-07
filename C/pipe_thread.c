#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

/* shared resource for thread */

char msg[20];
int waitseconds;

void *parent_function( void *ptr )
{
	int *pfd = ptr;

	printf("Parent function\n");
	getchar();
	write(pfd[1], msg, strlen(msg));
	printf("Parent function goes to sleep without closing write end.\n"
			"Causes read end to wait till write end closes\n");
	sleep(10);
	close(pfd[1]); /* Reader will see EOF */
	printf("\nPipe write end closes from parent\n");
}

void *child_function( void *ptr )
{
	char buf;
	int *pfd = (int *)ptr, retval;
	fd_set fds;
	struct timeval tv;

	FD_ZERO(&fds);
	FD_SET(pfd[0], &fds);

	/* Wait up to seconds. */
	tv.tv_sec = waitseconds;
	tv.tv_usec = 0;

	printf("child function\n");
	retval = select(pfd[0] + 1, &fds, NULL, NULL, &tv);
	/* Dont rely on the value of tv now! */
	if (retval == -1) {
		perror("select()");
	} else if (retval) {
		printf("Data is available now.\n");
		while(read(pfd[0], &buf, 1))
			write(STDOUT_FILENO, &buf, 1);
		/* recieve EOF as write end of pipe closed */
		/* FD_ISSET(0, &rfds) will be true. */
		write(STDOUT_FILENO, "\n", 1);
		printf("Write end of pipe cosed, hence read end recieves EOF\n");
	} else {
		printf("No data within %d seconds.\n", waitseconds);
	}
	close(pfd[0]); /* Reader will see EOF */
}

int main (int argc, char *argv[])
{
	int pfd[2], retval;
	pid_t cpid;
	pthread_t thread1, thread2;

	assert(argc == 3);

	waitseconds = atoi(argv[2]);
	strcpy(msg, argv[1]);

	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	retval = pthread_create( &thread1, NULL, parent_function, (void*) pfd);
	if (retval) {
		perror("Failed to create thread\n");
		exit(EXIT_FAILURE);
	}
	retval = pthread_create( &thread2, NULL, child_function, (void*) pfd);
	if (retval) {
		perror("Failed to create thread\n");
		exit(EXIT_FAILURE);
	}

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
}
