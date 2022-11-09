#if 0
	Mechanisms for exchanging data between processes
	Pipes are byte streams, can read arbitrary blocks of data, regardless of size of write
	Data passes through pipe sequentially 
	Pipes have a limited capacity
	on linux: F_SETPIPE_SZ 
	
#endif

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 10

int 
main(int argc, char *argv[])
{
	int pfd[2];
	char buf[BUF_SIZE];
	ssize_t num_read;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s string\n", argv[0]);
	}

	if (pipe(pfd) == -1)
	{
		perror("pipe");
	}

	switch (fork()) 
	{
		case -1:
			perror("fork");
		case 0:
			if (close(pfd[1]) == -1)
			{
				perror("close-child");
			}

			for (;;)
			{
				num_read = read(pfd[0], buf, BUF_SIZE);
				if (num_read == -1)
				{
					return 0;
				}
				if (num_read == 0)
				{
					break;
				}
				if (write(STDOUT_FILENO, buf, num_read) != num_read)
				{
					printf("child-partial/failed write");
				}
			}

			write(STDOUT_FILENO, "\n", 1);

			if (close(pfd[0]) == -1)
			{
				return 0;
			}
			return 0;
		default:
			if (close(pfd[0]) == -1)
			{
				perror("close-parent");
			}

			if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
			{
				printf("parent - partial/failed write");
			}

			if (close(pfd[1]) == -1)
			{
				perror("close");
			}

			wait(NULL);

			return 0;
	}

	return 0;
}
