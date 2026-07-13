#include "Player.h"
#include <Windows.h>

Player::Player()
{
    // 玩家出生在地图下方中间
    SetPosition(400, 700);
}

void Player::Control(Map& map)
{
    if (GetAsyncKeyState('W') & 0x8000)
    {
        SetDirection(Direction::UP);
        Move(map);
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
        SetDirection(Direction::DOWN);
        Move(map);
    }

    if (GetAsyncKeyState('A') & 0x8000)
    {
        SetDirection(Direction::LEFT);
        Move(map);
    }

    if (GetAsyncKeyState('D') & 0x8000)
    {
        SetDirection(Direction::RIGHT);
        Move(map);
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        Fire();          // 调用父类函数
    }

    UpdateBullet(map);     // 更新父类子弹
}