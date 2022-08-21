#pragma once

#include "struct.h"
#include <map>
#include <mutex>
#include <memory>

using namespace std;

//object에다가 mutex를 추가해야함. 그래야 renderer에서도 사용가능.

class Object
{
private:
    int socket;
    Object_type type;
    Position location;
    Rotation direction;

protected:
    Object(Object_type type,Position location,Rotation direction):
    type{type},location{location},direction{direction} {}

public:
    static Object create(Object_type type,Position location,Rotation direction);
    Object(){}
    ~Object(){}
    Object_type get_type();
    Position get_location();
    void set_location(Position location);
    void add_x(float x);
    void add_y(float y);
    Rotation get_direction();
    void set_direction(Rotation direction);
};

class Object_holder
{
private:
    map<string,Object> objects;
public:
    Object_holder(){}
    ~Object_holder(){}
    void add(string name,Object_type type,Position location,Rotation direction);
    map<string,Object>::iterator begin();
    map<string,Object>::iterator end();
    void set_location(string name,Position location);
};