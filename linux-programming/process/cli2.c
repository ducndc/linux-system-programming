/* Demo program to show the command line arguments of process*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
    int count = 0;

    printf("\nDemonstrate the command line arguments");

    if (strstr(argv[1], "add"))
    {
        printf("\n addition result = (%d)\n", atoi(argv[2]) + atoi(argv[3] ));
    }
    else if (strstr(argv[1],"sub"))
    {
        printf("\n subtraction result = (%d)\n", atoi(argv[2]) - atoi(argv[3] ));
    }
    else
    {
        printf("\nwrong input\n");
    }
}
