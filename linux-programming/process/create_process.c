#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t child_pid;
	child_pid = fork();

	if (child_pid < 0)
	{
		printf("fork failed");
		return 0;
	}
	else if (0 == child_pid)
	{
		printf("child process successfully created!");
		printf("child_PID = %d, parent_PID = %d", getpid(), getppid());
	}
	else
	{
		wait(NULL);
		printf("parent process successfully created!");
		printf("child_PID = %d, parent_PID = %d", getpid(), getppid());
	}

	return 0;
}
