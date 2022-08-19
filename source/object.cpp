#include "object.h"

Object Object::create(int socket,Type type,Position location,Rotation direction)
{
    Object new_object(socket,type,location,direction);
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
void Object::set_location(Position location)
{
    this->location = location;
}
void Object::add_x(float x)
{
    location.x += x;
}
void Object::add_y(float y)
{
    location.y += y;
}

void Object::set_direction(Rotation direction)
{
    this->direction = direction;
}

void Object_holder::add(int socket,Type type,Position location,Rotation direction)
{
    objects[socket] = Object::create(socket,type,location,direction);
}

map<int,Object>::iterator Object_holder::begin()
{
    return objects.begin();
}
map<int,Object>::iterator Object_holder::end()
{
    return objects.end();
}
