#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    char buffer[100];
    char* hello = "Mohid";
    int fd;
    char message[100];
    struct sockaddr_in server;
    memset(&server , 0 , sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port= htons(8888);
    fd=socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        printf("not making socket\n");
        exit(1);
    }
    connect(fd, (const struct sockaddr *)&server, sizeof(server));
    send(fd, hello, strlen(hello), 0);
    int n = recv(fd, buffer, 100, 0);
    buffer[n] = '\0';
    printf("server : %s\n", buffer);
    while(1)
    {
       int id = fork();
        if(id>0)
        {
            scanf("%s",message);
            send(fd, message, strlen(message), 0);
        }
        else
        {
            int n = recv(fd, buffer, 100, 0);
            buffer[n] = '\0';
            printf("%s\n", buffer);
        }
    }
    
    
}