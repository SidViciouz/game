#include "player.h"

string Player::get_name()
{
    return name;
}
void Player::set_name(string name)
{
    this->name = name;
}
Position Player::get_position()
{
    return position;
}
void Player::set_position(Position position)
{
    this->position = position;
}
Rotation Player::get_rotation()
{
    return rotation;
}
void Player::set_rotation(Rotation rotation)
{
    this->rotation = rotation;
}
Player Player::create(Position position,Rotation rotation,string name){
    Player new_player{position,rotation,name};

    return new_player;
}
