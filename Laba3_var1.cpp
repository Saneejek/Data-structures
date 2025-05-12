#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Функция для поиска пути с использованием DFS
bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, int exitX, int exitY) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Проверяем, вышли ли мы за границы лабиринта или наткнулись на стену или уже посещенную клетку
    if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 1 || visited[x][y]) {
        return false;
    }

    // Если достигли выхода, возвращаем true
    if (x == exitX && y == exitY) {
        return true;
    }

    // Помечаем текущую клетку как посещенную
    visited[x][y] = true;

    // Ищем путь в четырех направлениях
    if (dfs(maze, visited, x + 1, y, exitX, exitY) ||
        dfs(maze, visited, x - 1, y, exitX, exitY) ||
        dfs(maze, visited, x, y + 1, exitX, exitY) ||
        dfs(maze, visited, x, y - 1, exitX, exitY)) {
        return true;
    }

    // Если путь не найден, возвращаем false
    return false;
}

bool canEscapeAll(vector<vector<int>>& maze, vector<pair<int, int>>& entries, vector<pair<int, int>>& exits) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (size_t i = 0; i < entries.size(); ++i) {
        int entryX = entries[i].first;
        int entryY = entries[i].second;
        int exitX = exits[i].first;
        int exitY = exits[i].second;

        if (!dfs(maze, visited, entryX, entryY, exitX, exitY)) {
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

    if (canEscapeAll(maze, entries, exits)) {
        cout << "All people can escape the maze." << endl;
    } else {
        cout << "Not all people can escape the maze." << endl;
    }

    return 0;
}
