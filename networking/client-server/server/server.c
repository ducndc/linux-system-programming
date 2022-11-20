#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

void update_file_list();

void func(int connfd)
{
    char buff[SIZE];
    char file_name[SIZE];
    char path_name[SIZE];

    strcpy(path_name, "files/");
    bzero(buff, SIZE);
    FILE *fp;

    for (;;)
    {
        read(connfd, buff, sizeof(buff));
        if (strncmp(buff, "LIST", 4) == 0)
        {
            printf("Client request to get file list in server\n");
            update_file_list();
            send_file_list(connfd);
        }
        if (0 == strncmp(buff, "GET", 3))
        {
            printf("Client request to get file list in server\n");
            write(connfd, "ok", 2);
            bzero(buff, sizeof(buff));
            read(connfd, buff, sizeof(buff));
            strncpy(file_name, buff, sizeof(buff));

            printf("Client get %s \n", file_name);

            strcat(path_name, file_name);
            printf("%s\n", path_name);
            fp = fopen(path_name, "r");
            if (fp == -1)
            {
                printf("fp failed\n");
            }
            send_file(fp, connfd);
            write(connfd, "complete", 8);
        }
        if (0 == strncmp(buff, "exit", 4))
        {
            break;
        }
    }

}

int send_file_list(int connfd)
{
    char buff[SIZE];
    FILE *p_fd;
    char data[SIZE];

    p_fd = fopen("list.txt", "r");

    while (fgets(data, SIZE, p_fd) != NULL)
    {
        write(connfd, data, sizeof(data));
        printf("%s", data);
        bzero(data, SIZE);
    }
    write(connfd, "complete", 8);
}

int send_file(FILE *fp, int sockfd)
{
    printf("sending file ...\n");
    char data[SIZE] = {0};
    int total_data = 0;
    while(fgets(data, SIZE, fp) != NULL)
    {
        if(send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("Error in sending data");
            exit(1);
        }
        printf("data: %s", data);
        bzero(data, SIZE);
    }
    write(sockfd, "complete", 8);
    printf("end send_file\n");
    return total_data;
}

void update_file_list()
{
    printf("update_file_list\n");
    system("ls -1 files > list.txt");
}

int main()
{
    int sockfd, connfd, len;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) 
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("server accept the client...\n");
    }

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
