#pragma once

#include <stdexcept>
#include <iostream>
#include "listening.h"
#include "socket.h"

using namespace std;

class Server
{
private:
    Socket listening_socket;
    Listening listening;
    Event_list event_list;
    bool is_game_over;
    

public:
    Server() = delete;
    Server(char* address,int16_t port,int queue_size):
        listening_socket{address,port,queue_size},listening{listening_socket.get_socket()},
        event_list{30}, is_game_over{false} {}
    ~Server(){}
    void run();
};