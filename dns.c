#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(int argc , char *argv[])
{
    if (argc < 2)  {
        printf("Please specify the server port.");

        return 1;
    }
    int port = atoi(argv[1]);
    
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[100];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        return 1;
    }
    puts("Socket created.");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(socket_desc, (struct sockaddr *) &server , sizeof(server)))
    {
        perror("bind failed. Error");
        
        return 1;
    }
    puts("Binding done.");

    listen(socket_desc , 3);
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    while( (read_size = recv(client_sock , client_message , 100, 0)) > 0 )
    {
        char *message = "Hello from dns";
        write(client_sock , message, strlen(message));
    }
    
    return 0;
}

