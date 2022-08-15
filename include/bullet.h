#pragma once

#include "struct.h"
#include <vector>
#include <iostream>

using namespace std;

class Bullet
{
private:
    Position location;
    Rotation direction;
    static Bullet create(Position location,Rotation direction);
    //생성된 시간 추가해야함.

protected:
    Bullet() = delete;
    Bullet(Position location,Rotation direction):
    location{location}, direction{direction} {}
public:
    ~Bullet(){}
    friend class Bullet_holder;
};

class Bullet_holder
{
private:
    vector<Bullet> bullets;
public:
    Bullet_holder(){}
    ~Bullet_holder(){}
    void create(Position location,Rotation direction);
    void print();
};