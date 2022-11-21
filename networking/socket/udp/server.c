#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define SIZE        1024
#define PORT        8080

#define PRINT(s)    (printf(#s))

int send_file(FILE *p_fp, int sockfd, struct sockaddr_in addr)
{
    printf("send_file\n");
    char data[SIZE] = {0};
    int total_bytes = 0;
    while (fgets(data, SIZE, p_fp) != NULL)
    {
        if ((total_bytes += sendto(sockfd, data, sizeof(data), 0, 
            (struct sockaddr*)&addr, sizeof(addr))) == -1)
        {
            perror("Error in sending data");
            exit(-1);
        }
        bzero(data, SIZE);
    }
    sendto(sockfd, "END", 3, 0, (struct sockaddr*)&addr, sizeof(addr));
    fclose(p_fp);
    return total_bytes;
}

int main(int argc, char *argv[])
{
    int sockfd;
    int bind_event;
    FILE *p_fp;
    struct sockaddr_in server_addr;
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Error in socket");
        exit(-1);
    }
    
    PRINT(Sever socket created\n);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    
    bind_event = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (bind < 0)
    {
        perror("Error in Binding");
        exit(-1);
    }
    
    PRINT(Binding Successfull\n);
    addr_size = sizeof(server_addr);

    recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&server_addr, &addr_size);
   
    p_fp = fopen(argv[1], "r");

    printf("Number %d bytes sent to client\n", send_file(p_fp, sockfd, server_addr));

    printf("Sent file successfully to client\n");
    close(sockfd);

    return 0;
}
