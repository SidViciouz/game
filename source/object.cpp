#include "object.h"

Object Object::create(Object_type type,Position location,Rotation direction)
{
    Object new_object(type,location,direction);
    return new_object;
}
Object_type Object::get_type()
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

void Object_holder::add(string name,Object_type type,Position location,Rotation direction)
{
    objects[name] = Object::create(type,location,direction);
}

map<string,Object>::iterator Object_holder::begin()
{
    return objects.begin();
}
map<string,Object>::iterator Object_holder::end()
{
    return objects.end();
}
void Object_holder::set_location(string name,Position location)
{
    objects[name].set_location(location);
}
