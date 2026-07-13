#include "Explosion.h"

Explosion::Explosion()
{
    alive = false;
}

void Explosion::Play(int x, int y)
{
    this->x = x;
    this->y = y;

    radius = 4;
    timer = 20;      // ³ÖÐø20Ö¡

    alive = true;
}

void Explosion::Update()
{
    if (!alive)
        return;

    radius += 2;

    timer--;

    if (timer <= 0)
        alive = false;
}

void Explosion::Draw()
{
    if (!alive)
        return;

    setlinecolor(RED);
    circle(x, y, radius);

    setlinecolor(YELLOW);
    circle(x, y, radius - 4);

    setlinecolor(WHITE);
    circle(x, y, radius - 8);
}

bool Explosion::IsAlive()
{
    return alive;
}