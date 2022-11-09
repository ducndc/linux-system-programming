#include <unistd.h>
#include <stdio.h>

int main()
{
    int ret;

    ret = truncate("./test.txt", 45);
    if (ret == -1)
    {
        perror("trancate");
        return -1;
    }

    return 0;
}