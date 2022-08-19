#pragma once

#include "socket.h"
#include "renderer.h"
#include "input.h"
#include "object.h"
#include <iostream>

class Client
{
private:
    Socket client_socket;
    Renderer renderer;
    Input input;
    bool is_game_over;
    Object_holder object_holder;

public:
    Client() = delete;
    Client(char* address,int16_t port):
    client_socket{address,port}, is_game_over{false}, renderer{object_holder} {}
    ~Client(){}
    void run();
};