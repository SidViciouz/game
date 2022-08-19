#pragma once

#include "struct.h"
#include <map>
#include <mutex>
#include <memory>

using namespace std;

class Object
{
private:
    int socket;
    Type type;
    Position location;
    Rotation direction;

protected:
    Object(int socket,Type type,Position location,Rotation direction):
    socket{socket},type{type},location{location},direction{direction} {}

public:
    static Object create(int socket,Type type,Position location,Rotation direction);
    Object(){}
    ~Object(){}
    Type get_type();
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
    map<int,Object> objects;
public:
    Object_holder(){}
    ~Object_holder(){}
    void add(int socket,Type type,Position location,Rotation direction);
    map<int,Object>::iterator begin();
    map<int,Object>::iterator end();
};