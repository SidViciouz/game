#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdexcept>
#include <cstring>

using namespace std;

class Socket
{

private:
    int sk;

public:
    Socket() = delete;
    Socket(char* address,int16_t port,int queue_size);
    ~Socket(){}
    int get_socket();
};