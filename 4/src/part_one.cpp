#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Position {
    int row;
    int col;
};

enum Direction {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

Direction directions[] = {TOP, BOTTOM, LEFT, RIGHT, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

bool valid_pos(int rowCount, int colCount, Position& pos) {
    if (pos.row < 0 || pos.row >= rowCount || pos.col < 0 || pos.col >= colCount) {
        return false;
    }

    return true;
}

void move_position(Position& pos, Direction direction) {
    switch(direction) {
        case TOP:
            pos.row--;
            break;
        case BOTTOM:
            pos.row++;
            break;
        case LEFT:
            pos.col--;
            break;
        case RIGHT:
            pos.col++;
            break;
        case TOP_LEFT:
            pos.row--;
            pos.col--;
            break;
        case TOP_RIGHT:
            pos.row--;
            pos.col++;
            break;
        case BOTTOM_LEFT:
            pos.row++;
            pos.col--;
            break;
        case BOTTOM_RIGHT:
            pos.row++;
            pos.col++;
            break;
    }
}

bool xmas_check(vector<vector<char>>& grid, int rowCount, int colCount, Position pos, Direction direction) {
    move_position(pos, direction);
    
    char expected[] = {'M', 'A', 'S'};

    for(int i = 0; i < 3; i++) {
        if(!valid_pos(rowCount, colCount, pos)) return false;
        if(grid[pos.row][pos.col] != expected[i]) return false;
        move_position(pos, direction);
    }

    return true;
}

void check_each_direction(vector<vector<char>>& grid, int rowCount, int colCount, Position pos, int& answer) {
    for (Direction direction : directions) {
        if (xmas_check(grid, rowCount, colCount, pos, direction)) {
            answer++;
        }
    }
}

int main()
{
    string file_name = "4/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open())
    {
        cout << "Failed to open file\n";
        return 1;
    }

    int answer = 0;

    vector<vector<char>> grid;

    string line;

    while (getline(input_file, line, '\n')) {
        vector<char> line_chars;
        for (char c : line) {
            line_chars.push_back(c);
        }
        grid.push_back(line_chars);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = grid[i][j];
            if (c == 'X') {
                Position pos = {
                    i,
                    j
                };

                check_each_direction(grid, rows, cols, pos, answer);
            }
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}