# Winsock Code Example
Socket programming code example written in C, only works in Windows.

## Installation
### Clone repository
```sh
git clone --recursive https://github.com/manucabral/winsock-example.git
cd winsock-example
```

## Usage
### Makefile
Build in command line with `make`
```sh
make
```
Run server and client in two different terminals
```sh
make run_server ip=127.0.0.1 port=8888
make run_client ip=127.0.0.1 port=8888
```

### Manually
Compile using gcc
```sh
gcc windows_client.c -lws2_32 -o windows_client
gcc windows_server.c -lws2_32 -o windows_server
```
Run server and client in two diferent terminals
```sh
windows_client 127.0.0.1 8888
windows_server 127.0.0.1 8888
```
