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

        bool sequenceValid = false; 

        for (size_t i = 0; i < line_nums.size(); i++) {
            vector<int> skipping;

            skipping.assign(line_nums.begin(), line_nums.end());
            skipping.erase(skipping.begin() + i);

            bool increasing = true;
            bool decreasing = true;
            bool skipValid = true; 

            for (size_t j = 1; j < skipping.size(); j++) {
                int diff = abs(skipping[j] - skipping[j-1]);
                if (diff < 1 || diff > 3) {
                    skipValid = false;
                    break;
                }

                if (skipping[j] > skipping[j-1]) {
                    decreasing = false;
                } else if (skipping[j] < skipping[j-1]) {
                    increasing = false;
                }

                if (!increasing && !decreasing) {
                    skipValid = false;
                    break;
                }
            }

            if (skipValid && (increasing || decreasing)) {
                sequenceValid = true;
                break;
            }
        }

        if (sequenceValid) {
            safe++;
        }
    }

    cout << "Total safe sequences: " << safe << endl;

    input_file.close();

    return 0;
}