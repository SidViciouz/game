#pragma once

struct Position
{
    float x;
    float y;
    float z;

    Position operator+= (Position& other_position)
    {
        x += other_position.x;
        y += other_position.y;
        z += other_position.z;

        return {x,y,z};
    }
    Position operator+= (Position&& other_position)
    {
        x += other_position.x;
        y += other_position.y;
        z += other_position.z;

        return {x,y,z};
    }
    Position operator-= (Position& other_position)
    {
        x -= other_position.x;
        y -= other_position.y;
        z -= other_position.z;

        return {x,y,z};
    }
    Position operator-= (Position&& other_position)
    {
        x -= other_position.x;
        y -= other_position.y;
        z -= other_position.z;

        return {x,y,z};    }
};

struct Rotation
{
    float roll;
    float pitch;
    float yaw;

    Rotation operator+= (Rotation& other_position)
    {
        roll += other_position.roll;
        pitch += other_position.pitch;
        yaw += other_position.yaw;

        return {roll,pitch,yaw};
    }
    Rotation operator+= (Rotation&& other_position)
    {
        roll += other_position.roll;
        pitch += other_position.pitch;
        yaw += other_position.yaw;

        return {roll,pitch,yaw};    
    }
    Rotation operator-= (Rotation& other_position)
    {
        roll -= other_position.roll;
        pitch -= other_position.pitch;
        yaw -= other_position.yaw;

        return {roll,pitch,yaw};
    }
    Rotation operator-= (Rotation&& other_position)
    {
        roll -= other_position.roll;
        pitch -= other_position.pitch;
        yaw -= other_position.yaw;

        return {roll,pitch,yaw};    
    }
};

struct Shoot
{
    bool pressed;
    bool shoot;
};

enum Object_type
{
    PLAYER,
    BULLET
};