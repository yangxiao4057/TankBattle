#pragma once

#include "Common.h"
#include "Map.h"
#include "Bullet.h"

class Tank
{
protected:

    int x;
    int y;

    int speed;

    Direction direction;

    // ×Óµ¯
    Bullet bullet;

    int hp;

    bool alive;
public:
    Tank();

    void Move(Map& map);

    int GetX();

    int GetY();

    void Draw();

    void Fire();

    void UpdateBullet(Map& map);

    void SetDirection(Direction dir);

    void SetPosition(int x, int y);

    void TakeDamage(int damage);

    bool IsAlive();

    int GetHP();

    bool IsHit(int bx, int by);

    Bullet& GetBullet();

    bool IsCollide(int nextX, int nextY, Tank& other);
};