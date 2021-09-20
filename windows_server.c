#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

// Winsock library
#pragma comment(lib, "ws2_32.lib")

#define MAX_PENDING 5
#define RECEIVE_BUFFER_SIZE 32

void error(char *message)
{
    fprintf(stderr, "%s: %d\n", message, WSAGetLastError());
    exit(1);
    return;
}

void close(SOCKET so)
{
    closesocket(so);
    WSACleanup();
    return;
}

void handle_client(int client_socket)
{
    char buffer[RECEIVE_BUFFER_SIZE];
    char message[200] = "Welcome to the server!\n";
    int receive_message_size;

    send(client_socket, message, strlen(message) + 1, 0);

    if ((receive_message_size = recv(client_socket, buffer, RECEIVE_BUFFER_SIZE, 0)) < 0)
        error("Error on receive data.\n");

    while (receive_message_size > 0)
    {
        //if (send(client_socket, buffer, receive_message_size, 0) != receive_message_size)
            //error("Send message failed.\n");
        buffer[receive_message_size] = '\0';
        printf("[TCP Client]: %s\n", buffer);

        scanf("%s", message);
        printf("[Server]: %s\n", message);
        send(client_socket, message, strlen(message) + 1, 0);

        if ((receive_message_size = recv(client_socket, buffer, RECEIVE_BUFFER_SIZE, 0)) < 0)
            error("Error on receive data.\n");
    }

    puts("Closing client socket..");
    closesocket(client_socket);
}

int main(int argc, char *argv[])
{
    SOCKET server_so, client_so;
    WSADATA wsa;
    char *ip;
    int bytes_received;
    unsigned int client_length;
    unsigned short port;
    struct sockaddr_in server, client;

    if (argc != 3)
    {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        error("Failed WSAStartup.\n");

    printf("Winsock Initialised.\n");

    if ((server_so = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        error("Failed socket.\n");

    printf("Socket created.\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    if (bind(server_so, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
        error("Bind failed.\n");

    if (listen(server_so, MAX_PENDING) < 0)
        error("Listen failed.\n");

    puts("Waiting for incoming connections..");

    while (1)
    {
        client_length = sizeof(client);

        if ((client_so = accept(server_so, (struct sockaddr *)&client, &client_length)) < 0)
            error("Error on accept.\n");

        printf("New connection accepted %s\n", inet_ntoa(client.sin_addr));
        handle_client(client_so);
    }

    close(server_so);
    return 0;
}