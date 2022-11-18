#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE        1024
#define IP_ADDRESS  "127.0.0.1"
#define PORT        8080

int send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};
    int total_data = 0;
    while(fgets(data, SIZE, fp)!=NULL)
    {
        if((total_data = send(sockfd, data, sizeof(data), 0)) == -1)
        {
            perror("Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }

    return total_data;
}

void update_file_list()
{
    system("ls -1 files > list.txt");
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(sockfd, 10); 

    accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

    return 0;
}