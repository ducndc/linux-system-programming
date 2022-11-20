#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

int show_file(int sockfd);
int get_file(int sockfd);

void write_file(int sockfd, char *file_name)
{
	printf("write_file\n");
    int n; 
    FILE *fp;
    char buff[SIZE];

    fp = fopen(file_name, "w");
    if(fp == NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while (1)
    {
        n = recv(sockfd, buff, SIZE, 0);
        if (strncmp(buff, "complete", 8) == 0)
        {
        	printf("=========\n");
        	break;
        }
        fprintf(fp, "%s", buff);
        printf("%s", buff);
        bzero(buff, SIZE);
    }
    
}

void func(int sockfd)
{
	char buff[SIZE];
	bzero(buff, sizeof(buff));
	int a;
	while (a != 3)
	{
		printf("press 1: list\npress 2: get file\npress 3: exit\n");
		scanf("%d", &a);
		if (a == 1)
		{
			strncpy(buff, "LIST", 4);
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff));

			show_file(sockfd);
		}
		else if (a == 2)
		{
			get_file(sockfd);
		}
		else if (a == 3)
		{
			write(sockfd, "exit", 4);
			break;
		}
	}
}

int show_file(int sockfd)
{
	printf("show_file\n");

	char buff[SIZE];
	bzero(buff, sizeof(buff));
	for (;;)
	{
		read(sockfd, buff, sizeof(buff));
		if (strncmp(buff, "complete", 8) == 0)
		{
			printf("=========\n");
			break;
		}
		printf("%s", buff);
		bzero(buff, sizeof(buff));
	}
	return 0;
}

int get_file(int sockfd)
{
	char buff[SIZE];
	char file_name[SIZE];
	write(sockfd, "GET", 3);
	bzero(buff, sizeof(buff));

	read(sockfd, buff, sizeof(buff));
	if (0 == strncmp(buff, "ok", 2))
	{
		bzero(buff, sizeof(buff));
		printf("enter file name: ");
		scanf("%s", &file_name);
		strncpy(buff, file_name, sizeof(file_name));
		write(sockfd, buff, sizeof(buff));
		write_file(sockfd, file_name);
	}
	printf("end get file\n");
}


int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
	{
		printf("connected to the server..\n");
	}

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
