#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    string file_name = "2/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open())
    {
        cout << "Failed to open file\n";
        return 1;
    }

    int safe = 0;

    string line;

    while (getline(input_file, line))
    {
        vector<int> line_nums;

        stringstream ss(line);

        int currNum;

        while (ss >> currNum)
        {
            line_nums.push_back(currNum);
        }

        if (line_nums.size() <= 1)
        {
            continue;
        }

        bool valid = true;
        bool increasing = true;
        bool decreasing = true;

        for (size_t i = 1; i < line_nums.size(); i++)
        {
            if (line_nums[i] > line_nums[i - 1])
            {
                decreasing = false;
            }
            else if (line_nums[i] < line_nums[i - 1])
            {
                increasing = false;
            }

            if ((!increasing && !decreasing) || (abs(line_nums[i] - line_nums[i-1]) > 3) || (abs(line_nums[i] - line_nums[i-1]) < 1))
            {
                valid = false;
                break;
            }
        }

        if (valid) {
            safe++;
        }
    }

    cout << "Total safe sequences: " << safe << endl;

    input_file.close();

    return 0;
}