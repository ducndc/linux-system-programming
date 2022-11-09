#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h> 

int main() 
{ 
    int fd;
    int sz;
    int fd1; 
    int sz1;
    char buf[20] = {0};
    char buf1[20] = {0};

    fd = open("input.txt", O_RDONLY); 
    fd1 = open("input1.txt", O_RDONLY);
    if (fd < 0 || fd1 < 0)
    {
        perror("Error:"); exit(1); 
    } 

    sz = read(fd, buf, 10); 
    sz1 = read(fd1, buf1, 10);
    printf("call 1 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
    printf("call 2 - called read. fd1 = %d,  %d bytes  were read.\n", fd1, sz1);
    buf[sz] = '\0'; 
    printf("Read bytes are as follows: \n<%s>\n", buf); 

    printf("\n Note the next set of bytes read from file, it is continuos\n");

    sz = read(fd, buf, 11); 
    printf("call 2 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
    buf[sz] = '\0'; 
    printf("Read bytes are as follows:\n<%s>\n", buf); 

    sz = read(fd, buf, 10); 
    printf("call 3 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
    if(sz == 0)
    {
        printf("EOF Reached\n");
    }

    close(fd);
} 