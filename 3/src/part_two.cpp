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

    string enabled_text;
    bool enabled = true;
    size_t pos = 0;

    std::sregex_iterator end;

    std::regex control_pattern(R"((?:do|don't)\(\))");
    std::sregex_iterator control_iter(contents.begin(), contents.end(), control_pattern);

    while (control_iter != end) {
        size_t control_pos = control_iter->position();
        if (enabled) {
            enabled_text += contents.substr(pos, control_pos - pos);
        }
        enabled = (control_iter->str() == "do()");
        pos = control_pos + control_iter->length();
        control_iter++;
    }

    if (enabled) {
        enabled_text += contents.substr(pos);
    }

    int result = 0;

    std::regex mul_pattern(R"(mul\(\d{1,3},\s*\d{1,3}\))");
    std::sregex_iterator regex_iter(enabled_text.begin(), enabled_text.end(), mul_pattern);

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