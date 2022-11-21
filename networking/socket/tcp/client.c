#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE        1024
#define IP_ADDRESS  "127.0.0.1"
#define PORT        8080

#define PRINT(s) (printf(#s))

int write_file(int sockfd)
{
    int num_bytes;
    FILE *p_fp;
    char *p_file_name = "received_server_file.txt";
    char buffer[SIZE];

    p_fp = fopen(p_file_name, "w");
    
    if (p_fp == NULL)
    {
        perror("Error in creating file");
        exit(-1);
    }

    while (1)
    {
        num_bytes = recv(sockfd, buffer, SIZE, 0);
        if (num_bytes <= 0)
        {
            return -1;
        }
        fprintf(p_fp, "%s", buffer);
        bzero(buffer, SIZE);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char client_IP[16];
    unsigned int client_port;
    socklen_t sock_len;
    int sockfd;
    int connection;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Error in socket");
        exit(-1);
    }
    
    PRINT(Server socket created\n);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    connection = connect(sockfd, (struct sockaddr*)&server_addr, 
                    sizeof(server_addr));

    if (connection == -1)
    {
        perror("Error in connecting");
        exit(-1);
    }

    PRINT(Connected to server\n);
    
    bzero(&client_addr, sizeof(client_addr));
    sock_len = sizeof(client_addr);
    getsockname(sockfd, (struct sockaddr*)&client_addr, &sock_len);
    inet_ntop(AF_INET, &client_addr.sin_addr, client_IP, sizeof(client_IP));
    client_port = ntohs(client_addr.sin_port);

    printf("Client Ip: %s:%d\n", client_IP, client_port);
    printf("File received successfully from server\n"); 
    write_file(sockfd);

    return 0;
}
