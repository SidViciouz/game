#pragma once

#include <GLFW/glfw3.h>
#include <thread>
#include <math.h>
#include <cstring>
#include <functional>
#include <time.h>
#include <sys/socket.h>
#include "object.h"
#include "message.h"

using namespace std;

void input_thread(Object& object,mutex& object_mutex,Shoot& shoot,mutex& shoot_mutex);

class Input
{
private:
    mutex object_mutex;
    Object object;
    mutex shoot_mutex;
    Shoot shoot;

public:
    Input();
    ~Input(){}
    void send_change(int socket);
    void register_player(int socket);
};