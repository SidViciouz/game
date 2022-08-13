#include "listening.h"
#include <stdio.h>

Listening::Listening(int listening_socket):
listening_socket{listening_socket}
{
    kq = kqueue();
    change_list.add(listening_socket,EVFILT_READ);
}

void Listening::wait(Event_list& event_list)
{
    int number_of_event = kevent(kq,change_list.get_data(),change_list.get_size(),
    event_list.get_data(),event_list.get_size(),NULL);
    
    change_list.clear();
}

void Listening::add(int socket,int filter)
{
    change_list.add(socket,filter);
}
