windows_client: windows_client.c
	gcc windows_client.c -lws2_32 -o windows_client

run:
	./windows_client