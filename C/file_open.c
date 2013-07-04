#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
	int fd;
	char buf;

	if (argc < 2)
		printf("Please pass file name to open as comand line\n");

	printf("%s\n", argv[1]);

	fd = open(argv[1], O_RDONLY, 0);

	if (fd < 0)
		printf("file not opened\n");

	while (read(fd, &buf, 1))
		putchar(buf);

	close(fd);
	return 0;
}
