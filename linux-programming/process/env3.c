#include <stdio.h>
#include <stdlib.h>

/* the command line arguments variable is visible only in main(), 
where as the environmnet variables are visible all over the process*/

void call_func1(void);

int main () 
{

   putenv("PARAM1=1024");

   printf("PATH : (%s)\n", getenv("PATH"));
   printf("HOME : (%s)\n", getenv("HOME"));
   printf("PARAM1 :(%s)\n", getenv("PARAM1"));

   call_func1();
   
   return(0);
}

void call_func1(void)
{
    printf("inside function call_func1: PARAM1 :(%s)\n", getenv("PARAM1"));
}
