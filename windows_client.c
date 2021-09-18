#include <stdio.h>
#include <winsock.h>

// Winsock library
#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_BUFFER_SIZE 32

int main(int argc, char *argv[])
{
    SOCKET so;
    WSADATA wsa;
    char *server_ip;
    unsigned short server_port;
    struct sockaddr_in server;

    if(argc < 2){
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    server_ip = argv[1];
    server_port = atoi(argv[2]);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Error: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock Initialised.\n");

    /**
     * @brief Creates a socket and return socket descriptor
     * AF_INET: IP Version 4 (Address Family)
     * SOCK_STREAM: Oriented to TCP protocol (Type)
     * 0: (Protocol)
     */
    if((so = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{   
		printf("Error on create: %d\n" , WSAGetLastError());
        return 1;
	}

    printf("Socket created.\n");

    /**
     * @brief Setting server values
     * sin_family: Target addrees family (IP Version 4)
     * sin_addr.s_addr: Target server ip conversion to unsigned long value
     * sin_port = Value in TCP/IP network byte order (using htons)
     */
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(server_port);

    /**
     * @brief Establishes a connection
     * so: Target socket descriptor.
     * (struct sockaddr *) &server: A pointer to the sockaddr structure to which the connection should be established
     * sizeof server: The lenght in bytes of the sockaddr struct.
     */
    if (connect(so, (struct sockaddr *) &server, sizeof server) < 0){
        printf("Failed to connect: %ld\n", WSAGetLastError());
        closesocket(so);
        WSACleanup();   
        return 1;
    }

    printf("Connected to %s:%d\n", server_ip, server_port);

    closesocket(so);
    WSACleanup();   
    return 0;
}