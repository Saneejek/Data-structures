#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Функция для поиска пути с использованием DFS
bool dfsAnyExit(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, vector<pair<int, int>>& exits) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Проверяем, вышли ли мы за границы лабиринта или наткнулись на стену или уже посещенную клетку
    if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 1 || visited[x][y]) {
        return false;
    }

    // Проверяем, достигли ли мы любого из выходов
    for (auto exit : exits) {
        if (x == exit.first && y == exit.second) {
            return true;
        }
    }

    // Помечаем текущую клетку как посещенную
    visited[x][y] = true;

    // Ищем путь в четырех направлениях
    if (dfsAnyExit(maze, visited, x + 1, y, exits) ||
        dfsAnyExit(maze, visited, x - 1, y, exits) ||
        dfsAnyExit(maze, visited, x, y + 1, exits) ||
        dfsAnyExit(maze, visited, x, y - 1, exits)) {
        return true;
    }

    // Если путь не найден, возвращаем false
    return false;
}

bool canEscapeAny(vector<vector<int>>& maze, vector<pair<int, int>>& entries, vector<pair<int, int>>& exits) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (auto entry : entries) {
        int entryX = entry.first;
        int entryY = entry.second;

        if (!dfsAnyExit(maze, visited, entryX, entryY, exits)) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> maze = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    vector<pair<int, int>> entries = {{0, 0}, {0, 4}};
    vector<pair<int, int>> exits = {{4, 0}, {4, 4}};

    if (canEscapeAny(maze, entries, exits)) {
        cout << "All people can escape the maze through any exit." << endl;
    } else {
        cout << "Not all people can escape the maze through any exit." << endl;
    }

    return 0;
}
