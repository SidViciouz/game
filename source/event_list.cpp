#include "event_list.h"

Event_list::Event_list(int number)
{
    event_list.resize(number);
}

void Event_list::add(int socket,int filter)
{
    struct kevent new_event;

    EV_SET(&new_event,socket,filter,EV_ADD|EV_ENABLE,0,0,NULL);
    event_list.push_back(new_event);
}
void Event_list::clear()
{
    event_list.clear();
}
struct kevent* Event_list::get_data()
{
    return event_list.data();
}
int Event_list::get_size()
{
    return event_list.size();
}
vector<struct kevent>::iterator Event_list::first()
{
    return event_list.begin();
}
vector<struct kevent>::iterator Event_list::end()
{
    return event_list.end();
}