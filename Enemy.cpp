#include "Enemy.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy()
{
    // 出生在上方
    SetPosition(200, 200);
    speed = 4;
    moveTimer = 0;
    fireTimer = 0;
    hp = 1;
    alive = true;
}


void Enemy::AI(Map& map)
{
    moveTimer++;
    fireTimer++;

    // 每30帧换一次方向
    if (moveTimer >= 30)
    {
        moveTimer = 0;

        int r = rand() % 4;

        SetDirection((Direction)r);
    }

    // 移动
    if (moveTimer % 2 == 0)
    {
        Move(map);
    }


    // 每60帧开火
    if (fireTimer >= 60)
    {
        fireTimer = 0;
        Fire();
    }

    UpdateBullet(map);
}
