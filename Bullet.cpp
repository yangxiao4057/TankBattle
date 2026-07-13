#include "Bullet.h"

Bullet::Bullet()
    : x(0), y(0), speed(10), direction(Direction::UP), alive(false)
{
}

void Bullet::Init(int x, int y, Direction dir)
{
    this->x = x;
    this->y = y;
    this->direction = dir;

    alive = true;
}

void Bullet::Update()
{
    if (!alive) return;

    switch (direction)
    {
    case Direction::UP:    y -= speed; break;
    case Direction::DOWN:  y += speed; break;
    case Direction::LEFT:  x -= speed; break;
    case Direction::RIGHT: x += speed; break;
    }

    if (x < 0 || x > WINDOW_WIDTH ||
        y < 0 || y > WINDOW_HEIGHT)
    {
        alive = false;
    }
}

void Bullet::Draw()
{
    if (!alive) return;

    setfillcolor(WHITE);
    solidcircle(x, y, 3);
}

bool Bullet::IsAlive()
{
    return alive;
}
int Bullet::GetX() const
{
    return x;
}

int Bullet::GetY() const
{
    return y;
}
void Bullet::Destroy()
{
    alive = false;
}