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

public:
    Object(){}
    ~Object(){}
    friend class Object_holder;
};

class Object_holder
{
private:
    vector<Object> objects;
public:
    Object_holder(){}
    ~Object_holder(){}
};