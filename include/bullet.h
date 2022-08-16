#pragma once

#include "struct.h"
#include <vector>
#include <iostream>
#include "my_time.h"

using namespace std;

class Bullet
{
private:
    Position location; //getter, setter 만들어야함.
    Rotation direction;
    uint64_t time;
    static Bullet create(Position location,Rotation direction,uint64_t time);
    //생성된 시간 추가해야함.

protected:
    Bullet() = delete;
    Bullet(Position location,Rotation direction,uint64_t time);
public:
    ~Bullet(){}
    Position get_location();
    void set_location(Position new_location);
    Rotation get_direction();
    void set_direction(Rotation new_direction);
    friend class Bullet_holder;
};

class Bullet_holder
{
private:
    vector<Bullet> bullets;
public:
    Bullet_holder(){}
    ~Bullet_holder(){}
    void create(Position location,Rotation direction,uint64_t time);
    void update();
    void print(uint64_t current_time);
};