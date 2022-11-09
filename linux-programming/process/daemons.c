#if 0
	A daemon is a process that runs in the background, not connecting to any controlling
	terminal. Daemons are normally started at boot time, are run as root or some other
	special user (such as apache or postfix), and handle system-level tasks. As a convention,
	the name of a daemon often ends in d (as in crond and sshd), but this is not required or
	even universal.
#endif 

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(void)
{
	pid_t pid;
	int i;

	/* create new process */
	pid = fork();
	if (pid == -1)
	{
		return -1;
	}
	else if (pid != 0)
	{
		exit(EXIT_SUCCESS);
	}

	/* create new session and process group */
	if (setsid() == -1)
	{
		return -1;
	}

	/* set the working directory to the root directory */
	if (chdir("/") == -1)
	{
		return -1;
	}

	/* close all open file -- NR_OPEN is overkill, but works */
	for (i = 0; i < 3; i++)
	{
		close(i);
	}

	/* redirect fd's 0, 1, 2 to /dev/null */
	open("/dev/null", O_RDWR); 	/* stdin */
	dup(0); 					/* stdout */
	dup(0);						/* stderroe */

	/* do its daemon things... */

	return 0;
}
