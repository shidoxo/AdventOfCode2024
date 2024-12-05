#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

enum LineType {
    RULE,
    UPDATE
};

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);

    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool isValidUpdate(vector<vector<int>>& rules, vector<int>& update) {
    unordered_map<int, int> positions;

    for (size_t i = 0; i < update.size(); i++) {
        positions[update[i]] = i;
    }

    for (const auto& rule : rules) {
        int first = rule[0];
        int second = rule[1];

        if (positions.find(first) == positions.end() || 
            positions.find(second) == positions.end()) {
            continue;
        }

        if (positions[first] >= positions[second]) {
            return false;
        }
    }

    return true;
}

int main()
{
    string file_name = "5/input.txt";

    ifstream input_file(file_name, ios::in);

    if (!input_file.is_open())
    {
        cout << "Failed to open file\n";
        return 1;
    }

    int answer = 0;

    vector<vector<int>> rules;
    vector<vector<int>> updates;

    LineType lineType = RULE;

    string line;

    while (getline(input_file, line, '\n')) {
        if (line.empty()) {
            lineType = UPDATE;
        }

        if (lineType == RULE) {
            vector<int> rule;
            vector<string> splitLine = split(line, '|');
            for (string token : splitLine) {
                int parsedToken = stoi(token);
                rule.push_back(parsedToken);
            }
            rules.push_back(rule);
        } else {
            vector<int> update;
            vector<string> splitLine = split(line, ',');
            for (string token : splitLine) {
                int parsedToken = stoi(token);
                update.push_back(parsedToken);
            }
            updates.push_back(update);
        }
    }

    vector<vector<int>> validUpdates;

    for (auto update: updates) {
        bool valid = isValidUpdate(rules, update);
        if (valid) {
            validUpdates.push_back(update);
        }
    }

    for (const auto& update: validUpdates) {
        if (!update.empty()) {
            size_t middle = update.size() / 2;
            answer += update[middle];
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}