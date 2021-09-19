#include <stdio.h>
#include <winsock.h>

// Winsock library
#pragma comment(lib, "ws2_32.lib")

#define MAX_PENDING 5

void close(SOCKET so)
{
    closesocket(so);
    WSACleanup();
    return;
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
    {
        printf("Error: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock Initialised.\n");

    if ((server_so = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Error on create: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Socket created.\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    if (bind(server_so, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        pritnf("Bind failed: %d", WSAGetLastError());
        close(server_so);
        return 1;
    }

    if (listen(server_so, MAX_PENDING) < 0){
        pritnf("Listen failed: %d", WSAGetLastError());
        close(server_so);
        return 1;
    }

    print("Waiting for incoming connections..");

    client_length = sizeof(client);
    client_so = accept(server_so, (struct sockaddr *)&client, &client_length);
    
    close(server_so);
    return 0;
}