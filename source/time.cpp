#include "my_time.h"

Time::Time()
{
    time = mach_absolute_time();
}
uint64_t Time::get_current_time()
{
    return time;
}
void Time::update()
{
    time = mach_absolute_time();
}