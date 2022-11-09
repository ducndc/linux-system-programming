#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

int main() 
{ 
    pid_t id;
    printf("Parent Process : Executed by parent process before fork() - PID = (%d)\n", getpid()); 
    id = fork();  // from this point of code, the child and parent process both execute 
    if (id < 0 )
    {
        printf("\nfork failed\n");
        exit(-1);
    }
    if (id > 0)
    {
        printf("\nParent Process: I have created child process withID = (%d)\n", id);

    }else
    {
        printf("\nI am child process,  id value is (%d)\n",id) ;
        printf("\nchild process id is (%d)\n",getpid());
        printf("\nThe creator of child process is (%d)\n", getppid());
    }
  
    return 0; 
} 
