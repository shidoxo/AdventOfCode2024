#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position {
    int row;
    int col;
};

bool isInBounds(int rows, int cols, Position pos) {
    if (pos.row < 0 || pos.row >= rows || pos.col < 0 || pos.col >= cols) {
        return false;
    }
    
    return true;
}

char checkFront(vector<vector<char>>& grid, int& rows, int& cols, Position& pos, Direction& dir) {
    switch (dir) {
        case UP:
            if (isInBounds(rows, cols, Position { pos.row-1, pos.col })) {
                return grid[pos.row-1][pos.col];
            } else {
                return 'X';
            }
            break;
        case DOWN:
            if (isInBounds(rows, cols, Position { pos.row+1, pos.col })) {
                return grid[pos.row+1][pos.col];
            } else {
                return 'X';
            }
            break;
        case LEFT:
            if (isInBounds(rows, cols, Position { pos.row, pos.col-1 })) {
                return grid[pos.row][pos.col-1];
            } else {
                return 'X';
            }
            break;
        case RIGHT:
            if (isInBounds(rows, cols, Position { pos.row, pos.col+1 })) {
                return grid[pos.row][pos.col+1];
            } else {
                return 'X';
            }
            break;
        default:
            return 'X';
            break;
    }
}

void turnDirection(Direction& dir) {
    switch (dir) {
        case UP:
            dir = RIGHT;
            break;
        case RIGHT:
            dir = DOWN;
            break;
        case DOWN:
            dir = LEFT;
            break;
        case LEFT:
            dir = UP;
            break;
    }
}

void moveForward(Position& pos, Direction dir) {
    switch (dir) {
        case UP:
            pos.row--;
            break;
        case DOWN:
            pos.row++;
            break;
        case LEFT:
            pos.col--;
            break;
        case RIGHT:
            pos.col++;
            break;
    }   
}

int main() {
    string file_name = "6/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open()) {
        cout << "Failed to open file\n";
        return 1;
    }

    int answer = 0;

    vector<vector<char>> grid;

    Direction currDir = UP;

    Position guardPosition;

    string line;
    int currRow = 0; 
    int currCol = 0;

    while (getline(input_file, line, '\n')) {
        vector<char> line_chars;
        for (char c : line) {
            if (c == '^') {
                guardPosition = {
                    currRow,
                    currCol
                };
            }
            line_chars.push_back(c);
            currCol++;
        }
        grid.push_back(line_chars);
        currRow++;
        currCol = 0;
    }

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    while (isInBounds(rows, cols, guardPosition)) {

        visited[guardPosition.row][guardPosition.col] = true;

        char front = checkFront(grid, rows, cols, guardPosition, currDir);

        if (front == 'X') {
            break;
        }

        else if (front == '#') {
            turnDirection(currDir);
            continue;
        }

        moveForward(guardPosition, currDir);
    }

    for (vector<bool>& row : visited) {
        for (const bool& col : row) {
            if (col) {
                answer++;
            }
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}