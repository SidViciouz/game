#pragma once

#include "socket.h"
#include "renderer.h"
#include "input.h"
#include <iostream>

class Client
{
private:
    Socket client_socket;
    Renderer renderer;
    Input input;
    bool is_game_over;

public:
    Client() = delete;
    Client(char* address,int16_t port):
    client_socket{address,port}, is_game_over{false} {}
    ~Client(){}
    void run();
};