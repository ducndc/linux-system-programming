// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd1; 
	char str1[80]; 
	// FIFO file path 
	char *my_fifo = "/tmp/my_fifo"; 

	// First open in read only and read 
    fd1 = open(my_fifo, O_RDONLY); 
	printf("Process %d\n", getpid());
	
	while (1) 
	{ 
		read(fd1, str1, 80); 
		// Print the read string and close 
		printf("User: %s\n", str1); 
	} 

	close(fd1); 

	return 0; 
}
