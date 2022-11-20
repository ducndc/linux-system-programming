#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

#define SIZE 80
#define PORT 8080
#define SA struct sockaddr
#define MAX_CLIENT 10
#define TRUE             1
#define FALSE            0

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

    p_fd = fopen("list.txt", "rb");

    while (fgets(data, SIZE, p_fd) != NULL)
    {
        write(connfd, data, sizeof(data));
        bzero(data, SIZE);
    }
    write(connfd, "complete", 8);
}

int send_file(FILE *fp, int sockfd)
{
    printf("sending file ...\n");
    char data[SIZE] = {0};
    int total_data = 0;
    while (fread(data, SIZE, 1, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("Error in sending data");
            exit(1);
        }
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
    int sockfd;
    int connfd;
    int len;
    int on = 1;
    int timeout;
    int rc;
    struct sockaddr_in servaddr;
    struct sockaddr_in cli;
    struct pollfd fds[MAX_CLIENT];
    int nfds = 1;
    int current_size = 0;
    int new_sd = -1;
    int end_server = FALSE;
    int compress_array = FALSE;

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

    rc = setsockopt(sockfd, SOL_SOCKET,  SO_REUSEADDR,
                      (char *)&on, sizeof(on));
    if (rc < 0)
    {
      perror("setsockopt() failed");
      close(sockfd);
      return (-1);
    }

    rc = ioctl(sockfd, FIONBIO, (char *)&on);
    if (rc < 0)
    {
      perror("ioctl() failed");
      close(sockfd);
      return (-1);
    }

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
    if ((listen(sockfd, 32)) != 0) 
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
    len = sizeof(cli);
    memset(fds, 0, sizeof(fds));

    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

    timeout = (3 * 60 * 1000); //3 min

    do 
    {
        printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, timeout);

        if (rc < 0)
        {
          perror("  poll() failed");
          break;
        }

        if (rc == 0)
        {
          printf("  poll() timed out.  End program.\n");
          break;
        }

        current_size = nfds;
        for (int  i = 0; i < current_size; i++)
        {
            if (fds[i].revents == 0)
            {
                continue;
            }

            if (fds[i].revents != POLLIN)
            {
                printf("Error revents = %d\n", fds[i].revents);
                break;
            }
            if (fds[i].fd == sockfd)
            {
                printf("Listening socket is readable\n");
                do 
                {
                    new_sd = accept(sockfd, (SA*)&cli, &len);
                    if (new_sd < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                          perror("  accept() failed");
                          end_server = TRUE;
                        }
                        break;
                    }
                    printf("New incoming connection %d\n", new_sd);
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                } 
                while (new_sd != -1);
            }
            else 
            {
                printf("  Descriptor %d is readable\n", fds[i].fd);

                func(fds[i].fd);
            }
        }

        if (compress_array)
        {
          compress_array = FALSE;
          for (int i = 0; i < nfds; i++)
          {
            if (fds[i].fd == -1)
            {
              for(int j = i; j < nfds; j++)
              {
                fds[j].fd = fds[j+1].fd;
              }
              i--;
              nfds--;
            }
          }
        }

    }
    while (end_server == FALSE);

    // // Accept the data packet from client and verification
    // connfd = accept(sockfd, (SA*)&cli, &len);
    // if (connfd < 0) 
    // {
    //     printf("server accept failed...\n");
    //     exit(0);
    // }
    // elses
    // {
    //     printf("server accept the client...\n");
    // }

    // // Function for chatting between client and server
    // func(connfd);

    // // After chatting close the socket
    // close(sockfd);
}
