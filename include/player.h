#pragma once

#include <string>
#include "struct.h"

using namespace std;

class Player
{

private:
    Position position;
    Rotation rotation;
    string name;

protected:
    Player(Position position, Rotation rotation,string name)
    : position{position}, rotation{rotation}, name{name} {}

public:
    Player(){}
    ~Player(){}
    string get_name();
    void set_name(string name);
    Position get_position();
    void set_position(Position position);
    Rotation get_rotation();
    void set_rotation(Rotation rotation);
    static Player create(Position position,Rotation rotation,string name);
};