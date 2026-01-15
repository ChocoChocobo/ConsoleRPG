#ifndef ASTAR_H
#define ASTAR_H


#include <vector>
#include <string>


namespace AStar {
	struct Cell { int x; int y; };


	// Возвращает вектор клеток от старта до цели (включая обе). Если пути нет — пустой вектор.
	std::vector<Cell> AStarSearch(const std::vector<std::string>& map, int height, int width, Cell start, Cell end);


	// Утилита: печать карты с отмеченным путем (не изменяет оригинал)
	void PrintMapWithPath(const std::vector<std::string>& map, int height, int width, const std::vector<Cell>& path, Cell start, Cell end);
}


#endif // ASTAR_H