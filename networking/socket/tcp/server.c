#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE        1024
#define IP_ADDRESS  "127.0.0.1"
#define IP_PROTOCOL 0
#define PORT        8080

#define PRINT(s)    (printf(#s))

int send_file(FILE *p_fp, int sockfd)
{
    char data[SIZE] = {0};
    int total_bytes = 0;
    while (fgets(data, SIZE, p_fp) != NULL)
    {
        if ((total_bytes += send(sockfd, data, sizeof(data), 0)) == -1)
        {
            perror("Error in sending data");
            exit(-1);
        }
        bzero(data, SIZE);
    }
    return total_bytes;
}

int main(int argc, char *argv[])
{
    int sockfd;
    int bind_event;
    int listen_event;
    int new_sock;
    FILE *p_fp;
    struct sockaddr_in server_addr;
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Error in socket");
        exit(-1);
    }
    
    PRINT(Sever socket created\n);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    
    bind_event = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (bind < 0)
    {
        perror("Error in Binding");
        exit(-1);
    }
    
    PRINT(Binding Successfull\n);

    listen_event = listen(sockfd, 10);

    if (listen_event == 0)
    {
        PRINT(Listening...\n);
    }
    else
    {
        perror("Error in Listening");
        exit(-1);
    }
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    p_fp = fopen(argv[1], "r");
    
    printf("Number %d bytes sent to client\n", send_file(p_fp, new_sock));
    printf("Sent file successfully to client\n");
    close(sockfd);

    return 0;
}
