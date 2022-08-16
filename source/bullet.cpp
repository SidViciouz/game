#include "bullet.h"

Bullet::Bullet(Position location,Rotation direction,uint64_t time):
location{location}, direction{direction}, time{time}
{

}

Bullet Bullet::create(Position location,Rotation direction,uint64_t time)
{
    Bullet new_bullet(location,direction,time);
    return new_bullet;
};

Position Bullet::get_location()
{
    return location;
}
void Bullet::set_location(Position new_location)
{
    location = new_location;
}
Rotation Bullet::get_direction()
{
    return direction;
}
void Bullet::set_direction(Rotation new_direction)
{
    direction = new_direction;
}


void Bullet_holder::create(Position location,Rotation direction,uint64_t time)
{
    bullets.push_back(Bullet::create(location,direction,time));
}

void Bullet_holder::update()
{
    for(Bullet bullet : bullets)
    {
        //bullet의 위치 수정. bullet 객체에 past_time을 추가해야함. 
    }
}

void Bullet_holder::print(uint64_t current_time)
{
    for(Bullet bullet : bullets)
    {
        printf("location : %f %f %f, direction : %f %f %f time_passed : %d\n",
        bullet.location.x,bullet.location.y,bullet.location.z,
        bullet.direction.yaw,bullet.direction.pitch,bullet.direction.roll,
        current_time - bullet.time);
    }
}