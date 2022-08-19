#pragma once

#include "struct.h"
#include <vector>

using namespace std;

class Object
{
private:
    Type type;
    Position location;
    Rotation direction;
    static Object create(Type type,Position location,Rotation direction);

protected:
    Object() = delete;
    Object(Type type,Position location,Rotation direction):
    type{type},location{location},direction{direction} {}

public:
    ~Object(){}
    Type get_type();
    Position get_location();
    Rotation get_direction();
    friend class Object_holder;
};

class Object_holder
{
private:
    vector<Object> objects;
public:
    Object_holder(){}
    ~Object_holder(){}
    void create(Type type,Position location,Rotation direction);
    vector<Object>::iterator begin();
    vector<Object>::iterator end();
};