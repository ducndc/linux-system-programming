#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

    // fd = open("permission.txt", O_WRONLY | O_CREAT | O_TRUNC,
    //             S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
    fd = open("permission.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    
    if (fd == -1)
    {
        printf("error\n");
    }
    return 0;
}
