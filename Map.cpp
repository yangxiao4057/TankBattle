#include "Map.h"

//=====================================
// 构造函数
//=====================================

Map::Map()
{
    // 全部初始化为空地
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            map[i][j] = 0;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        map[0][i] = 1;
    }

    for (int i = 0; i < 26; i++)
    {
        map[25][i] = 1;
    }

    for (int i = 0; i < 26; i++)
    {
        map[i][0] = 1;
    }

    for (int i = 0; i < 26; i++)
    {
        map[i][25] = 1;
    }
    Generate();
    loadimage(
        &brickImg,
        _T("Resource\\brick.png"),
        32,
        32,
        true
    );
}
//void Map::Draw()
//{
//    setfillcolor(DARKGRAY);
//
//    for (int row = 0; row < 26; row++)
//    {
//        for (int col = 0; col < 26; col++)
//        {
//            if (map[row][col] == 1)
//            {
//                solidrectangle(
//                    col * 32,
//                    row * 32,
//                    col * 32 + 32,
//                    row * 32 + 32
//                );
//            }
//        }
//    }
//}
void Map::Draw()
{
    for (int row = 0; row < 26; row++)
    {
        for (int col = 0; col < 26; col++)
        {
            if (map[row][col] == 1)
            {
                putimage(
                    col * 32,
                    row * 32,
                    &brickImg
                );
            }
        }
    }
}
bool Map::IsWall(int row, int col)
{

    if (row < 0 || row >= 26 || col < 0 || col >= 26)
    {
        return true;
    }

    return map[row][col] == 1;
}
void Map::Generate()
{

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            map[i][j] = 0;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        map[0][i] = 1;
        map[25][i] = 1;
        map[i][0] = 1;
        map[i][25] = 1;
    }

    int count = 0;

    while (count < 50)
    {
        int r = rand() % 22 + 2;
        int c = rand() % 22 + 2;

        if (r > 19 && c > 10 && c < 15)
            continue;

        if (r < 5)
            continue;

        if (map[r][c] == 0)
        {
            map[r][c] = 1;
            count++;
        }
    }
}