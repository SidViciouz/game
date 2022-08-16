#pragma once

#include <mach/mach_time.h>

class Time
{
private:
    uint64_t time;
public:
    Time();
    ~Time(){}
    uint64_t get_current_time();
    void update();
};