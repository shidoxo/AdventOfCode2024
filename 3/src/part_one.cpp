#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    string file_name = "3/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open())
    {
        cout << "Failed to open file\n";
        return 1;
    }

    stringstream buffer;

    buffer << input_file.rdbuf();

    string contents = buffer.str();

    int result = 0;

    std::regex mul_pattern(R"(mul\(\d{1,3},\s*\d{1,3}\))");
    std::sregex_iterator regex_iter(contents.begin(), contents.end(), mul_pattern);
    std::sregex_iterator end;

    vector<string> matches;

    while(regex_iter != end) {
        string currStr = regex_iter->str();
        matches.push_back(currStr);
        regex_iter++;
    }

    std::regex arg_pattern(R"(\d{1,3})"); 

    for (string match: matches) {
        int res = 1;
        vector<int> nums;
        std::sregex_iterator match_iter(match.begin(), match.end(), arg_pattern);
        while(match_iter != end) {
            string currStr = match_iter->str();
            nums.push_back(std::stoi(currStr));
            match_iter++;
        }
        for (int num : nums) {
            res *= num;
        }
        result += res;
    }

    cout << "Result: " << result << endl;

    input_file.close();

    return 0;
}