#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Map
{
public:
    int height;
    int width;
    std::vector<std::string> grid;

    Map(int h = 10, int w = 20);

    // Простая генерация карты: границы стена, внутри случайно стены по fillPercent
    void GenerateRandom(int fillPercent = 20);
    void Print() const;
    bool IsWalkable(int x, int y) const;
};

#endif