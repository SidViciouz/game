#include "bullet.h"

Bullet Bullet::create(Position location,Rotation direction)
{
    Bullet new_bullet(location,direction);
    return new_bullet;
};
void Bullet_holder::create(Position location,Rotation direction)
{
    bullets.push_back(Bullet::create(location,direction));
}
void Bullet_holder::print()
{
    for(Bullet bullet : bullets)
    {
        printf("location : %f %f %f, direction : %f %f %f\n",
        bullet.location.x,bullet.location.y,bullet.location.z,
        bullet.direction.yaw,bullet.direction.pitch,bullet.direction.roll);
    }
}