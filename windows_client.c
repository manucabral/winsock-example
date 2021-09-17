#include <stdio.h>
#include <winsock.h>

// Winsock library
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
    SOCKET so;
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Error: %d", WSAGetLastError());
        return 1;
    }

    printf("Winsock Initialised.");

    /**
     * @brief Creates a socket and return socket descriptor
     * AF_INET: IP Version 4 (Address Family)
     * SOCK_STREAM: Oriented to TCP protocol (Type)
     * 0: (Protocol)
     */
    if((so = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{   
		printf("Error on create: %d" , WSAGetLastError());
        return 1;
	}

    printf("Socket created.");

    closesocket(so);
    WSACleanup();   
    return 0;
}