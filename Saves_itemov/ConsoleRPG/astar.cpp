#include "AStar.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

namespace AStar {

    static int DistanceToCell(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2); // манхэттен
    }

    struct Node
    {
        int x, y;
        int g;
        int f;
        Node* parent;
    };

    vector<Cell> AStarSearch(const vector<string>& map, int height, int width, Cell start, Cell end)
    {
        vector<vector<bool>> closed(height, vector<bool>(width, false));
        vector<vector<int>> gcost(height, vector<int>(width, numeric_limits<int>::max()));
        vector<vector<Node>> nodes(height, vector<Node>(width));

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                nodes[i][j].x = i;
                nodes[i][j].y = j;
                nodes[i][j].g = numeric_limits<int>::max();
                nodes[i][j].f = numeric_limits<int>::max();
                nodes[i][j].parent = nullptr;
            }
        }

        struct OpenItem { int x, y, g, f; };
        vector<OpenItem> open;

        gcost[start.x][start.y] = 0;
        nodes[start.x][start.y].g = 0;
        nodes[start.x][start.y].f = DistanceToCell(start.x, start.y, end.x, end.y);
        nodes[start.x][start.y].parent = nullptr;
        open.push_back({ start.x, start.y, 0, nodes[start.x][start.y].f });

        int dirX[4] = { -1, 1, 0, 0 };
        int dirY[4] = { 0, 0, -1, 1 };

        bool found = false;

        while (!open.empty())
        {
            // найти лучший элемент
            int bestIdx = 0;
            for (int i = 1; i < (int)open.size(); ++i)
            {
                if (open[i].f < open[bestIdx].f || (open[i].f == open[bestIdx].f && open[i].g < open[bestIdx].g))
                    bestIdx = i;
            }

            OpenItem cur = open[bestIdx];
            // удалить из открытого
            open.erase(open.begin() + bestIdx);

            int cx = cur.x;
            int cy = cur.y;

            if (closed[cx][cy]) continue;
            closed[cx][cy] = true;

            if (cx == end.x && cy == end.y)
            {
                found = true;
                break;
            }

            for (int k = 0; k < 4; ++k)
            {
                int nx = cx + dirX[k];
                int ny = cy + dirY[k];

                if (nx < 0 || nx >= height || ny < 0 || ny >= width) continue;
                if (map[nx][ny] == '+') continue; // стена
                if (closed[nx][ny]) continue;

                int newG = gcost[cx][cy] + 1;
                if (newG < gcost[nx][ny])
                {
                    gcost[nx][ny] = newG;
                    nodes[nx][ny].g = newG;
                    nodes[nx][ny].f = newG + DistanceToCell(nx, ny, end.x, end.y);
                    nodes[nx][ny].parent = &nodes[cx][cy];

                    open.push_back({ nx, ny, nodes[nx][ny].g, nodes[nx][ny].f });
                }
            }
        }

        vector<Cell> path;
        if (found)
        {
            Node* cur = &nodes[end.x][end.y];
            while (cur)
            {
                path.push_back({ cur->x, cur->y });
                cur = cur->parent;
            }
            reverse(path.begin(), path.end());
        }

        return path;
    }

    void PrintMapWithPath(const vector<string>& map, int height, int width, const vector<Cell>& path, Cell start, Cell end)
    {
        vector<string> copy = map;
        if (!path.empty())
        {
            for (size_t i = 1; i + 1 < path.size(); ++i)
            {
                copy[path[i].x][path[i].y] = '*';
            }
        }
        copy[start.x][start.y] = 'S';
        copy[end.x][end.y] = 'G';

        for (int i = 0; i < height; ++i) cout << copy[i] << '\n';
    }

}