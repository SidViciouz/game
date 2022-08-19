#include "socket.h"

Socket::Socket(char* address,int16_t port,int queue_size)
{
    sk = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(address);
    server_address.sin_port = htons(port);

    if(bind(sk,(const sockaddr*)&server_address,sizeof(server_address)) == -1)
    {
        throw runtime_error(string("bind error!"));
    }

    if(listen(sk,queue_size) == -1)
    {
        throw runtime_error(string("listen error!"));
    }

    if(fcntl(sk,F_SETFL,O_NONBLOCK) == -1)
    {
        throw runtime_error(string("fcntl error!"));
    }

}

Socket::Socket(char* address,int16_t port)
{
    sk = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(address);
    server_address.sin_port = htons(port);

    if(connect(sk,(const sockaddr*)&server_address,sizeof(server_address)) == -1)
    {
        throw runtime_error(string("connect error!"));
    }

    if(fcntl(sk,F_SETFL,O_NONBLOCK) == -1)
    {
        throw runtime_error(string("fcntl error!"));
    }
}


int Socket::get_socket()
{
    return sk;
}
