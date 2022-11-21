#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE        1024
#define PORT        8080 

#define PRINT(s) (printf(#s))

int write_file(int sockfd, struct sockaddr_in addr)
{
    printf("write_file\n");
    int num_bytes;
    FILE *p_fp;
    char *p_file_name = "received_server_file.txt";
    char buffer[SIZE];
    socklen_t addr_size;

    p_fp = fopen(p_file_name, "w");
    
    if (p_fp == NULL)
    {
        perror("Error in creating file");
        exit(-1);
    }
    addr_size = sizeof(addr);
    while (1)
    {
        recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);
        if (strncmp(buffer, "END", 3) == 0)
        {
            break; 
        }
        fprintf(p_fp, "%s", buffer);
        printf("%s", buffer);
        bzero(buffer, SIZE);
    }
    fclose(p_fp);
    return 0;
}

int main(int argc, char *argv[])
{
    char client_IP[16];
    unsigned int client_port;
    socklen_t sock_len;
    int sockfd;
    int rc;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buffer[SIZE];
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Error in socket");
        exit(-1);
    }
    
    PRINT(Client socket created\n);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    #if 1
    bzero(&client_addr, sizeof(client_addr));
    sock_len = sizeof(client_addr);
    getsockname(sockfd, (struct sockaddr*)&client_addr, &sock_len);
    inet_ntop(AF_INET, &client_addr.sin_addr, client_IP, sizeof(client_IP));
    client_port = ntohs(client_addr.sin_port);
    #endif

    rc = sendto(sockfd, "GET", 4, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
    if (rc == -1)
    {
        perror("error sending server\n");
        return -1;
    }

    printf("Client Ip: %s:%d\n", client_IP, client_port);
    printf("File received successfully from server\n"); 
    write_file(sockfd, server_addr);

    return 0;
}
