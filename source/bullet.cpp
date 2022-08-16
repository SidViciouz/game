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

bool Bullet::update(uint64_t time)
{
    past_time = current_time;
    current_time = time;

    if(current_time - create_time >= 50000000)
    {
        return false;
    }

    //위치 업데이트;

    float interval = (current_time - past_time)/1000000.0f;
    location += Position{direction.yaw*interval,direction.pitch*interval,direction.roll*interval};

    return true;
}

void Bullet_holder::create(Position location,Rotation direction,uint64_t current_time)
{
    bullets.push_back(Bullet::create(location,direction,current_time));
}

void Bullet_holder::update(uint64_t time)
{
    for(auto it = bullets.begin(); it != bullets.end();)
    {
        if(!it->update(time))
        {
            it = bullets.erase(it);
        }
        else
        {
            it++;
        }
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