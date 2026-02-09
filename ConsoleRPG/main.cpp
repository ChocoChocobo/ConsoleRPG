#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <conio.h> // Добавляем для работы с _getch()
#include "shpingalet.h"

using namespace std;

struct Cell // координаты символа в двумерном массиве символов
{
    int x;
    int y;
};

struct Node // узел, который хранит состояние клетки
{
    int x;
    int y;
    int g; // стомость от начала клетки
    int f; // полная стоимость (g + h), где h - расстояние до конца
    Node* parent; // предыдущий узел
};

int DistanceToCell(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* алгоритм, который возвращает указатель на клетку, которую мы ищем
Cell* AStarSearch(string* map, int height, int width, Cell start, Cell end, int &pathLength)
{
    // массив указателей на доступность узла
    bool** closed = new bool* [height]; // указываем строками на столбцы
    // массив указателей на стоимость узла
    int** gcost = new int* [height];
    Node** nodes = new Node * [height];

    // Инициализация поля и значений узлов
    for (int i = 0; i < height; i++)
    {
        // Выделяем строки
        closed[i] = new bool[width];
        gcost[i] = new int[width];
        nodes[i] = new Node[width];

        // Заполнение значений
        for (int j = 0; j < width; j++)
        {
            closed[i][j] = false;
            gcost[i][j] = 1000000000;
            nodes[i][j].x = i;
            nodes[i][j].y = j;
            nodes[i][j].g = 1000000000;
            nodes[i][j].f = 1000000000;
            nodes[i][j].parent = NULL;
        }
    }

    int maxOpen = height + width; // максимальное количество элементов в таблице
    int* openX = new int[maxOpen]; // массив X координат в открытых узлах
    int* openY = new int[maxOpen]; // массив Y координат в открытых узлах
    int* openG = new int[maxOpen]; // массив значений стоимости
    int* openF = new int[maxOpen]; // массив значений полной стоимости
    int openCount = 0; // текущее количество элементов 

    // Стартовая клетка
    gcost[start.x][start.y] = 0;
    nodes[start.x][start.y].g = 0;
    nodes[start.x][start.y].f = DistanceToCell(start.x, start.y, end.x, end.y);
    nodes[start.x][start.y].parent = NULL;

    // Открытые списки 
    openX[openCount] = start.x;
    openY[openCount] = start.y;
    openF[openCount] = nodes[start.x][start.y].f;
    openG[openCount] = 0;
    openCount++;

    //                влево, вправо, вниз, вверх
    int directionsX[4] = {-1, 1, 0, 0}; // Направления, куда может идти x
    int directionsY[4] = {0, 0, -1, 1}; // Направления, куда может идти x

    bool endFound = false;
    // Пока есть открытые узлы
    while (openCount > 0)
    {
        int bestId = 0;
        for (int i = 0; i < openCount; i++)
        {
            // Если текущий узел полной стоимости меньше лучшего узла полной стоимости ИЛИ текущий узел полной стоимости равен лучшему узлу полной стоимости И текущая стоимость от предыдущей клетки меньше лучше стоимости предыдущей клетки
            if (openF[i] < openF[bestId] || (openF[i] == openF[bestId] && openG[i] < openG[bestId]))
            {
                bestId = i;
            }
        }

        // Создаем переменные для работы с текущим узлом
        int currentX = openX[bestId];
        int currentY = openY[bestId];

        // Перемещаем последний элемент на место лучшего, затем присваиваем ему значения
        openCount--;
        openX[bestId] = openX[openCount];
        openY[bestId] = openY[openCount];
        openF[bestId] = openF[openCount];
        openG[bestId] = openG[openCount];

        // Если узел уже закрыт, пропускаем условие, либо помечаем текущий узел, как закрытый
        if (closed[currentX][currentY]) continue;
        closed[currentX][currentY] = true;

        // Если достигли целевого узла, отмечаем, что путь найден и выходим из цикла поиска
        if (currentX == end.x && currentY == end.y)
        {
            endFound = true;
            break;
        }

        // Для каждого соседа необходимо:                 
        for (int i = 0; i < 4; i++)
        {
            // 1. вычислять координаты
            int neighbourX = currentX + directionsX[i];
            int neighbourY = currentY + directionsY[i];
            // 2. проверять границы карты
            if (neighbourX < 0 || neighbourX >= height || neighbourY < 0 || neighbourY >= width) continue;
            // 3. проверять является ли сосед стеной
            if (map[neighbourX][neighbourY] == '+') continue;
            // 4. проверять закрыт ли сосед
            if (closed[neighbourX][neighbourY]) continue;

            int currentG = gcost[currentX][currentY] + 1;

            // Если найдена меньшая стоимость к соседу
            if (currentG < gcost[neighbourX][neighbourY])
            {
                // Обновляем значения у соседа
                gcost[neighbourX][neighbourY] = currentG;
                nodes[neighbourX][neighbourY].g = currentG;
                nodes[neighbourX][neighbourY].f = currentG + DistanceToCell(neighbourX, neighbourY, end.x, end.y);
                nodes[neighbourX][neighbourY].parent = &nodes[currentX][currentY];

                // Обновляем открытые списки
                openX[openCount] = neighbourX;
                openY[openCount] = neighbourY;
                openF[openCount] = nodes[neighbourX][neighbourY].f;
                openG[openCount] = nodes[neighbourX][neighbourY].g;
                openCount++;
            }
        }
    }

    Cell* path = NULL;
    // Если путь найден,восстанавливаем его по предыдущим узлам
    if (endFound)
    {
        cout << "Путь построен!" << endl;
        Node* currentNode = &nodes[end.x][end.y]; // текущий узел на момент нахождения конца
        pathLength = 0;
        //Подсчитываем сколько узлов потребовалось для нахождения цели
        while (currentNode != NULL)
        {
            pathLength++;
            currentNode = currentNode->parent;
        }
        // Создаем массив клеток с размером пути
        path = new Cell[pathLength];
        currentNode = &nodes[end.x][end.y];
        // Строим массив клеток в обратном порядке
        for (int i = pathLength - 1; i >= 0; i--)
        {
            path[i].x = currentNode->x;
            path[i].y = currentNode->y;
            currentNode = currentNode->parent;
        }
    }

    // Высвобождение памяти под 
    for (int i = 0; i < height; i++)
    {
        // поскольку мы работаем с массивом указателей на указатели, сперва необъодимо очистить память у строк, а затем и у самого массива
        delete[] closed[i];
        delete[] gcost[i];
        delete[] nodes[i];
    }
    delete[] closed;
    delete[] gcost;
    delete[] nodes;
    delete[] openX;
    delete[] openY;
    delete[] openF;
    delete[] openG;

    return path;
}

void PrintMap(string* map, int height, int width, Cell* path, Cell start, Cell end, int pathLength)
{
    string* mapCopy = new string[height];

    for (int i = 0; i < height; i++) mapCopy[i] = map[i];

    if (path != NULL)
    {
        for (int i = 1; i + 1 < pathLength; i++) mapCopy[path[i].x][path[i].y] = '*';
    }

    mapCopy[start.x][start.y] = 'S';
    mapCopy[end.x][end.y] = 'G';

    for (int i = 0; i < height; i++)
    {
        cout << mapCopy[i] << endl;
    }

    delete[] mapCopy;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string map[] =
    {
        // · - пустая клетка
        // + - стена
        // * - путь
        // S - старт
        // G - конец
        "···+·",
        "++·+·",
        "···+·",
        "·+++·",
        "·····"
    };

    int height = 5;
    int width = 5;

    Cell start; // структура клетки (символа в двумерном массиве)
    start.x = 0;
    start.y = 0;

    Cell end;
    end.x = 4;
    end.y = 4;

    // Каждый цикл мы вызываем функцию AStarSearch, которая возвращает набор клеток, по которым может передвигаться объект. После вызова этой функции переменная pathLength задается длиной пути, которую надо пройти
    // Пока координаты начальной точки НЕ равняются координатам конечной точки
    while (!(start.x == end.x && start.y == end.y))
    {
        int pathLength = 0;
        Cell* path = AStarSearch(map, height, width, start, end, pathLength);

        if (path != NULL)
        {
            PrintMap(map, height, width, path, start, end, pathLength);
            
            // ИНСТРУКЦИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ
            cout << "\nНажмите ПРОБЕЛ (SPACE) для следующего шага" << endl;
            cout << "Или любую другую клавишу для выхода" << endl;
            
            // Ждем ввода пользователя
            int key = _getch();
            
            // Если нажата клавиша SPACE (код 32)
            if (key == 32)
            {
                // Если длина пути больше двух, объект перемещается на следующий индекс набор клеток (первый)
                if (pathLength >= 2)
                {
                    start.x = path[1].x;
                    start.y = path[1].y;
                    cout << "Совершен шаг к цели!" << endl;
                }
                else
                {
                    start = end;
                }
            }
            else
            {
                cout << "Выход из программы..." << endl;
                delete[] path;
                break;
            }

            delete[] path;
        }
        else
        {
            cout << "Не удалось построить пути к цели!\n";
            break;
        }

        Sleep(300);
        system("cls");
    }

    if (start.x == end.x && start.y == end.y)
    {
        int pathLength = 0;
        Cell* path = AStarSearch(map, height, width, start, end, pathLength);
        PrintMap(map, height, width, path, start, end, pathLength);
        cout << "Враг добрался до вас!" << endl;
        // ИНИЦИАЛИЗАЦИЯ БОЯ
    }
    
    cout << "\nПрограмма завершена. Нажмите любую клавишу для выхода...";
    _getch();
    return 0;
}
