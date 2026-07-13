#include "Tank.h"
#include"Map.h"
#include"Enemy.h"
Tank::Tank()
{
    x = 400;
    y = 400;

    speed = 4;

    direction = Direction::UP;

    hp = 3;
    alive = true;
}
void Tank::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Tank::SetDirection(Direction dir)
{
    direction = dir;
}
void Tank::Fire()
{
    if (!bullet.IsAlive())
    {
        bullet.Init(x + 16, y + 16, direction);
    }
}
void Tank::UpdateBullet(Map& map)
{
    // 先移动子弹
    bullet.Update();

    // 如果子弹死了，直接返回
    if (!bullet.IsAlive()) return;

    // 子弹中心点
    int bx = bullet.GetX();
    int by = bullet.GetY();

    // 转换为地图格子
    int row = by / 32;
    int col = bx / 32;

    // 如果撞墙 → 消失
    if (map.IsWall(row, col))
    {
        bullet.Destroy();
    }
}
void Tank::Draw()
{
    // 设置填充颜色（绿色）
    setfillcolor(GREEN);

    // 坦克主体
    solidrectangle(x, y, x + 32, y + 32);

    // 炮塔
    setfillcolor(YELLOW);

    solidcircle(x + 16, y + 16, 6);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 3);

    int gunLength = 18;
    int cx = x + 16;
    int cy = y + 16;
    int gx = cx;
    int gy = cy;

    switch (direction)
    {
    case Direction::UP:
        line(cx, cy, cx, cy - gunLength);
        break;

    case Direction::DOWN:
        line(cx, cy, cx, cy + gunLength);
        break;

    case Direction::LEFT:
        line(cx, cy, cx - gunLength, cy);
        break;

    case Direction::RIGHT:
        line(cx, cy, cx + gunLength, cy);
        break;
    }

    // 绘制子弹
    bullet.Draw();

    settextcolor(RED);
    TCHAR hpText[20];
    _stprintf_s(hpText, _T("HP:%d"), hp);

    outtextxy(x, y - 20, hpText);
}
void Tank::Move(Map& map)
{
    int nextX = x;
    int nextY = y;

    switch (direction)
    {
    case Direction::UP:
        nextY -= speed;
        break;

    case Direction::DOWN:
        nextY += speed;
        break;

    case Direction::LEFT:
        nextX -= speed;
        break;

    case Direction::RIGHT:
        nextX += speed;
        break;
    }

    int left = nextX / 32;
    int right = (nextX + 31) / 32;
    int top = nextY / 32;
    int bottom = (nextY + 31) / 32;

    bool collision =
        map.IsWall(top, left) ||
        map.IsWall(top, right) ||
        map.IsWall(bottom, left) ||
        map.IsWall(bottom, right);

    if (!collision)
    {
        x = nextX;
        y = nextY;
    }
}
Bullet& Tank::GetBullet()
{
    return bullet;
}
void Tank::TakeDamage(int damage)
{
    hp -= damage;

    if (hp <= 0)
    {
        hp = 0;
        alive = false;
    }
}

bool Tank::IsAlive()
{
    return alive;
}

int Tank::GetHP()
{
    return hp;
}
bool Tank::IsHit(int bx, int by)
{
    if (bx > x && bx < x + 32 && by > y && by < y + 32)
    {
        return true;
    }

    return false;
}
int Tank::GetX()
{
    return x;
}

int Tank::GetY()
{
    return y;
}
bool Tank::IsCollide(int nextX, int nextY, Tank& other)
{

    if (!other.IsAlive())
        return false;

    if (this == &other)
        return false;

    return !(nextX + 32 <= other.GetX() ||
        nextX >= other.GetX() + 32 ||
        nextY + 32 <= other.GetY() ||
        nextY >= other.GetY() + 32);
}