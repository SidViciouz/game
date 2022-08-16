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
    uint64_t current_time;
    uint64_t past_time;
    uint64_t create_time;
    static Bullet create(Position location,Rotation direction,uint64_t current_time);
    //생성된 시간 추가해야함.

protected:
    Bullet() = delete;
    Bullet(Position location,Rotation direction,uint64_t time);
public:
    ~Bullet(){}
    void update(uint64_t time);
    friend class Bullet_holder;
};

class Bullet_holder
{
private:
    vector<Bullet> bullets;
public:
    Bullet_holder(){}
    ~Bullet_holder(){}
    void create(Position location,Rotation direction,uint64_t current_time);
    void update(uint64_t time);
    void print();
};