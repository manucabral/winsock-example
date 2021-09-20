
CC = gcc

all: windows_client windows_server 

windows_client: windows_client.c
	$(CC) windows_client.c -lws2_32 -o windows_client

windows_server: windows_server.c
	$(CC) windows_server.c -lws2_32 -o windows_server

run_client: windows_client
	windows_client $(ip) $(port)

run_server: windows_server
	windows_server $(ip) $(port)
