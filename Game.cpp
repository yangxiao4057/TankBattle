#include "Game.h"


Game::Game()
{
    running = true;
    gameOver = false;
    level = 1;
    playerDead = false;
    gameOverTimer = 0;
}


void Game::Init()
{
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

    SetWindowText(GetHWnd(), L"TankBattle");
    BeginBatchDraw();

    srand((unsigned)time(NULL));


    for (int i = 0; i < 3; i++)
    {
        Enemy e;
        e.SetPosition(100 + i * 200, 100);
        enemies.push_back(e);
    }
}



void Game::Run()
{
    while (running)
    {
        Update();

        Render();

        // 刷新屏幕
        FlushBatchDraw();

        Sleep(16);
    }

    EndBatchDraw();
}

//=================================
// 更新
//=================================

void Game::Update()
{
    // 游戏结束状态：显示爆炸动画后退出
    if (gameOver)
    {
        for (auto& ex : explosions)
            ex.Update();

        for (auto it = explosions.begin(); it != explosions.end();)
        {
            if (!it->IsAlive())
                it = explosions.erase(it);
            else
                ++it;
        }

        gameOverTimer--;
        if (gameOverTimer <= 0)
        {
            // 重新开始游戏
            level = 1;
            map.Generate();
            player = Player();
            enemies.clear();
            for (int i = 0; i < 3; i++)
            {
                Enemy e;
                e.SetPosition(100 + i * 200, 100);
                enemies.push_back(e);
            }
            explosions.clear();
            gameOver = false;
            gameOverTimer = 0;
        }

        return;
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        running = false;
    }

    player.Control(map);

    for (auto& e : enemies)
    {
        if (e.IsAlive())
        {
            e.AI(map);
        }
    }

    // 玩家子弹碰撞检测
    Bullet& pb = player.GetBullet();

    if (pb.IsAlive())
    {
        pb.Update();

        for (auto& e : enemies)
        {
            if (!e.IsAlive())
                continue;

            if (e.IsHit(pb.GetX(), pb.GetY()))
            {
                e.TakeDamage(1);
                pb.Destroy();
                if (!e.IsAlive())
                {
                    Explosion ex;

                    ex.Play(
                        e.GetX() + 16,
                        e.GetY() + 16
                    );

                    explosions.push_back(ex);
                }
                break;
            }
        }
    }

    // 敌人子弹碰撞检测
    for (auto& e : enemies)
    {
        if (!e.IsAlive())
            continue;

        Bullet& b = e.GetBullet();

        if (b.IsAlive())
        {
            b.Update();

            if (player.IsHit(b.GetX(), b.GetY()))
            {
                player.TakeDamage(1);
                b.Destroy();

                Explosion ex;
                ex.Play(player.GetX() + 16,
                    player.GetY() + 16);
                explosions.push_back(ex);
                if (!player.IsAlive()) {
                    gameOver = true;
                    gameOverTimer = 120;
                }
                break;
            }

        }
    }

    // 清理已死亡的敌人
    for (auto& e : enemies)
    {
        if (!e.IsAlive())
        {
            e.SetPosition(-100, -100);
        }
    }

    // 更新爆炸效果
    for (auto& e : explosions)
    {
        e.Update();
    }
    for (auto it = explosions.begin();
        it != explosions.end();)
    {
        if (!it->IsAlive())
            it = explosions.erase(it);
        else
            ++it;
    }
    bool allDead = true;

    for (auto& e : enemies)
    {
        if (e.IsAlive())
        {
            allDead = false;
            break;
        }
    }


    if (allDead)
    {
        NextLevel();
    }
}

void Game::Render()
{
    cleardevice();
    map.Draw();
    player.Draw();
    for (auto& e : enemies)
    {
        if (e.IsAlive())
            e.Draw();
    }
    settextcolor(YELLOW);
    TCHAR str[50];
    _stprintf_s(str, _T("LEVEL %d"), level);
    outtextxy(10, 10, str);
    for (auto& e : explosions)
    {
        e.Draw();
    }
    if (gameOver)
    {
        //Sleep(1000);
        settextcolor(RED);
        settextstyle(40, 0, _T("Consolas"));
        outtextxy(300, 400, _T("GAME OVER"));
        return;
    }

}
void Game::NextLevel()
{
    level++;

    map.Generate();

    player = Player();

    enemies.clear();

    for (int i = 0; i < 3 + level; i++)
    {
        Enemy e;
        e.SetPosition(100 + i * 80, 100);
        enemies.push_back(e);
    }

    gameOver = false;
}

//bool Game::TankCollision(
//    int nextX,
//    int nextY,
//    Tank* self)
//{
//    // 玩家
//    if(self!=&player)
//    {
//        if(player.IsAlive())
//        {
//            if(!(nextX+32<=player.GetX()||
//                 nextX>=player.GetX()+32||
//                 nextY+32<=player.GetY()||
//                 nextY>=player.GetY()+32))
//            {
//                return true;
//            }
//        }
//    }
//
//    // 所有敌人
//    for(auto& enemy:enemies)
//    {
//        if(!enemy.IsAlive())
//            continue;
//
//        if(self==&enemy)
//            continue;
//
//        if(!(nextX+32<=enemy.GetX()||
//             nextX>=enemy.GetX()+32||
//             nextY+32<=enemy.GetY()||
//             nextY>=enemy.GetY()+32))
//        {
//            return true;
//        }
//    }
//
//    return false;
//}