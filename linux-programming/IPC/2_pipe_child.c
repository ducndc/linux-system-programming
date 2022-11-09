#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 50

int main(int argc, char *argv[])
{
    int pfd[2];
    char buf[BUF_SIZE] = {};
    ssize_t num_read;

    /* Pipe file descriptors */
    if (pipe(pfd) == -1)
    {
        exit(-1);
    }

    switch (fork()) 
    {
        case -1:
            exit(-1);
        /* Create the pipe */
        case 0:
            /* Child - reads from pipe */
            if (close(pfd[1]) == -1)
            {    
                /* Write end is unused */
                exit(-1);
            }
            for (;;) 
            {
            /* Read data from pipe,  echo on stdout */
                strcpy(buf, "");
                num_read = read(pfd[0], buf, BUF_SIZE);
                if (num_read == -1)
                {
                    exit(-1);
                }
                if (num_read == 0)
                {
                    printf("\n child: parent closed write end\n");
                    break;
                }
                /* End-of-file */
                printf("\ndata received in child %d process is (%s)\n", getpid(), buf);
            }
            if (close(pfd[0]) == -1)
            {
                exit(-1);
            }
            break;
        default:
            /* Parent - writes to pipe */
            if (close(pfd[0]) == -1)
            {    
                /* Read end is unused */
                exit(-1);
            }
            printf("\nParent %d: sending user input string to child process - (%s)\n", getpid() , argv[1]);        
            write(pfd[1], argv[1], strlen(argv[1]));
            sleep(2);
            if (close(pfd[1]) == -1)
            {
                exit(-1);
            }
            printf("\n parent: closed write end\n");
            wait(NULL);
            exit(0);
        /* Child will see EOF */
        /* Wait for child to finish */
    }

    return 0;
}
