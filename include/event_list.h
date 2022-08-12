#pragma once

#include <vector>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

using namespace std;

class Event_list
{

private:
    vector<struct kevent> event_list;

public:
    Event_list(){}
    Event_list(int number);
    ~Event_list(){}
    void add(int socket,int filter);
    void clear();
    struct kevent* get_data();
    int get_size();
};