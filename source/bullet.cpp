#include "bullet.h"

Bullet::Bullet(Position location,Rotation direction,uint64_t current_time):
location{location}, direction{direction}, current_time{current_time}, past_time{current_time}, create_time{current_time}
{

}

Bullet Bullet::create(Position location,Rotation direction,uint64_t time)
{
    Bullet new_bullet(location,direction,time);
    return new_bullet;
}

void Bullet::update(uint64_t time)
{
    past_time = current_time;
    current_time = time;
    //위치 업데이트;
}

void Bullet_holder::create(Position location,Rotation direction,uint64_t current_time)
{
    bullets.push_back(Bullet::create(location,direction,current_time));
}

void Bullet_holder::update(uint64_t time)
{
    for(Bullet& bullet : bullets)
    {
        bullet.update(time);
    }
}

void Bullet_holder::print()
{
    for(Bullet bullet : bullets)
    {
        printf("location : %f %f %f, direction : %f %f %f time_passed : %d\n",
        bullet.location.x,bullet.location.y,bullet.location.z,
        bullet.direction.yaw,bullet.direction.pitch,bullet.direction.roll,
        bullet.current_time - bullet.past_time
        );
    }
}