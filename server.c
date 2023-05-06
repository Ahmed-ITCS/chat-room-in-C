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
    char buffer1[100];
    char* hello = "Hello - you are connected\n";
    int fd;
    struct sockaddr_in server , client;

    memset(&server , 0 , sizeof(server));
    memset(&client , 0 , sizeof(client));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port= htons(8888);
    fd=socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        printf("not making socket\n");
        exit(1);
    }
    if ( bind(fd, (const struct sockaddr *)&server, sizeof(server)) < 0 )
    {
        perror("not binding\n");
        exit(EXIT_FAILURE);
    }
    listen(fd , 10);
    int len = sizeof(client);
    int connection = accept(fd, (struct sockaddr *)&client, &len);
    int connection1 = accept(fd, (struct sockaddr *)&client, &len);
    int n = recv(connection, buffer, 100, 0);
    buffer[n] = '\0';
    int nn = recv(connection1, buffer1, 100, 0);
    buffer[nn] = '\0';
    printf("username : %s\n", buffer);
    printf("username : %s\n", buffer1);
    send(connection, hello, strlen(hello), 0);
    send(connection1, hello, strlen(hello), 0);
    //close(connection);
    //close(connection1);
    while(1)
    {
        //int connection = accept(fd, (struct sockaddr *)&client, &len);
        //int connection1 = accept(fd, (struct sockaddr *)&client, &len);
        if(connection >0 && connection1 >0)
        {
            int id = fork();
            if(id >0)
            {
                int n = recv(connection, buffer, 100, 0);
                buffer[n] = '\0';
                printf("client : %s\n", buffer);
                send(connection1, buffer, strlen(buffer), 0);
            }
            else
            {
                int n = recv(connection1, buffer1, 100, 0);
                buffer1[n] = '\0';
                printf("client : %s\n", buffer1);
                send(connection, buffer1, strlen(buffer1), 0);
            }
        }
         
        
    }
}