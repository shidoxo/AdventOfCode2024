#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> split(string input, char delim) {
    vector<string> result;

    stringstream ss(input);

    string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

bool is_true(pair<unsigned long long, vector<int>>& calibration) {
    unsigned long long target = calibration.first;

    vector<int>& nums = calibration.second;
    
    if (nums.empty()) return false;
    
    int n = nums.size();

    if (n == 1) return static_cast<unsigned long long>(nums[0]) == target;
    
    unsigned long long combinations = 1ULL << (n-1);
    
    for (unsigned long long combo = 0; combo < combinations; combo++) {
        unsigned long long result = static_cast<unsigned long long>(nums[0]);

        bool valid = true;
        
        for (int i = 0; i < n-1 && valid; i++) {
            unsigned long long next_num = static_cast<unsigned long long>(nums[i + 1]);
            
            if (combo & (1ULL << i)) {

                if (next_num != 0 && result > ULLONG_MAX / next_num) {
                    valid = false;
                    break;
                }

                result *= next_num;
            } else {
                if (result > ULLONG_MAX - next_num) {
                    valid = false;
                    break;
                }

                result += next_num;
            }
        }
        
        if (valid && result == target) {
            return true;
        }
    }
    
    return false;
}

int main() {
    string file_name = "7/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open())
    {
        cout << "Failed to open file\n";
        return 1;
    }

    unsigned long long answer = 0;

    vector<pair<unsigned long long, vector<int>>> calibrations;
    
    string line;

    while (getline(input_file, line, '\n')) {
        pair<unsigned long long, vector<int>> calibration;

        vector<string> splitString = split(line, ':');
        
        calibration.first = stoull(splitString[0]);
        
        if (splitString.size() > 1) {
            stringstream numbers(splitString[1]);
            string num;
            while (numbers >> num) {
                if (!num.empty()) {
                    calibration.second.push_back(stoi(num));
                }
            }
        }
        
        calibrations.push_back(calibration);
    }

    for(auto& calibration : calibrations) {
        if(is_true(calibration)) {
            answer += calibration.first;
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}