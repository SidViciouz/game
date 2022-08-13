#pragma once

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <vector>
#include "event_list.h"

using namespace std;

class Listening
{

private:
    int listening_socket;
    int kq;
    Event_list change_list;


public:
    Listening() = delete;
    Listening(int listening_socket);
    ~Listening(){}
    void wait(Event_list& event_list);
    void add(int socket,int filter);

};