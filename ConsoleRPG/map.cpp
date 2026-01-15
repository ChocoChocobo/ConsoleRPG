#include "Map.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Map::Map(int h, int w) : height(h), width(w)
{
}

void Map::GenerateRandom(int fillPercent)
{
    grid.clear();
    grid.resize(height);

    for (int i = 0; i < height; ++i)
    {
        grid[i].resize(width, '·');
    }

    // границы
    for (int x = 0; x < height; ++x)
    {
        grid[x][0] = '+';
        grid[x][width - 1] = '+';
    }
    for (int y = 0; y < width; ++y)
    {
        grid[0][y] = '+';
        grid[height - 1][y] = '+';
    }

    // случайные внутренние стены
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            int r = rand() % 100;
            if (r < fillPercent) grid[i][j] = '+';
            else grid[i][j] = '·';
        }
    }
}

void Map::Print() const
{
    for (int i = 0; i < height; ++i)
        cout << grid[i] << endl;
}

bool Map::IsWalkable(int x, int y) const
{
    if (x < 0 || x >= height || y < 0 || y >= width) return false;
    return grid[x][y] != '+';
}