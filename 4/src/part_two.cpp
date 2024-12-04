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
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

Direction directions[] = {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

bool valid_pos(int rowCount, int colCount, Position& pos) {
    if (pos.row < 0 || pos.row >= rowCount || pos.col < 0 || pos.col >= colCount) {
        return false;
    }

    return true;
}

void move_position(Position& pos, Direction direction) {
    switch(direction) {
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

bool xmas_check(vector<vector<char>>& grid, int rowCount, int colCount, Position pos) {
    Position top_left = pos;
    Position bottom_right = pos;

    move_position(top_left, TOP_LEFT);
    move_position(bottom_right, BOTTOM_RIGHT);

    if (!valid_pos(rowCount, colCount, top_left) || !valid_pos(rowCount, colCount, bottom_right)) {
        return false;
    }

    bool first_diagonal = 
        (grid[top_left.row][top_left.col] == 'M' && grid[bottom_right.row][bottom_right.col] == 'S') ||
        (grid[top_left.row][top_left.col] == 'S' && grid[bottom_right.row][bottom_right.col] == 'M');

    Position top_right = pos;
    Position bottom_left = pos;
    
    move_position(top_right, TOP_RIGHT);
    move_position(bottom_left, BOTTOM_LEFT);

    if (!valid_pos(rowCount, colCount, top_right) || !valid_pos(rowCount, colCount, bottom_left)) {
        return false;
    }

    bool second_diagonal = 
        (grid[top_right.row][top_right.col] == 'M' && grid[bottom_left.row][bottom_left.col] == 'S') ||
        (grid[top_right.row][top_right.col] == 'S' && grid[bottom_left.row][bottom_left.col] == 'M');

    return first_diagonal && second_diagonal;
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
            if (c == 'A') {
                Position pos = {
                    i,
                    j
                };

                if(xmas_check(grid, rows, cols, pos)) {
                    answer++;
                }
            }
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}