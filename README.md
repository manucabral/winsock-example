# Serat
Socket programming in C for Windows with a Server and Client example

## Installation
### Clone repository
```sh
git clone --recursive https://github.com/manucabral/winsock-example.git
cd winsock-example
```

### Usage
Build in command line with `make`
```sh
make
```
Run server and client (with two different terminal)
```sh
make run_server ip=127.0.0.1 port=8888
make run_client ip=127.0.0.1 port=8888
```
