#include "object.h"

Object Object::create(Type type,Position location,Rotation direction)
{
    Object new_object(type,location,direction);
    return new_object;
}
Type Object::get_type()
{
    return type;
}

Position Object::get_location()
{
    return location;
}
Rotation Object::get_direction()
{
    return direction;
}

void Object_holder::create(Type type,Position location,Rotation direction)
{
    objects.push_back(Object::create(type,location,direction));
}

vector<Object>::iterator Object_holder::begin()
{
    return objects.begin();
}
vector<Object>::iterator Object_holder::end()
{
    return objects.end();
}
