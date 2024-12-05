#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

enum LineType
{
    RULE,
    UPDATE
};

vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);

    string token;

    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

bool isValidUpdate(vector<vector<int>> &rules, vector<int> &update)
{
    unordered_map<int, int> positions;

    for (size_t i = 0; i < update.size(); i++)
    {
        positions[update[i]] = i;
    }

    for (const auto &rule : rules)
    {
        int first = rule[0];
        int second = rule[1];

        if (positions.find(first) == positions.end() ||
            positions.find(second) == positions.end())
        {
            continue;
        }

        if (positions[first] >= positions[second])
        {
            return false;
        }
    }

    return true;
}

vector<int> fixOrder(const vector<vector<int>> &rules, const vector<int> &update)
{
    unordered_map<int, unordered_set<int>> before;
    unordered_map<int, unordered_set<int>> after;

    for (int num : update)
    {
        before[num] = {};
        after[num] = {};
    }

    for (const auto &rule : rules)
    {
        int a = rule[0], b = rule[1];
        if (before.count(a) && before.count(b))
        {
            before[b].insert(a);
            after[a].insert(b);
        }
    }

    bool changed = true;

    while (changed)
    {
        changed = false;
        for (auto &[num, deps] : before)
        {
            size_t oldSize = deps.size();
            for (int dep : vector<int>(deps.begin(), deps.end()))
            {
                deps.insert(before[dep].begin(), before[dep].end());
            }
            if (deps.size() > oldSize)
                changed = true;
        }
    }

    vector<pair<int, int>> sortOrder;
    
    for (const auto &[num, deps] : before)
    {
        sortOrder.push_back({num, deps.size()});
    }

    sort(sortOrder.begin(), sortOrder.end(),
         [](const auto &a, const auto &b)
         {
             if (a.second != b.second)
                 return a.second < b.second;
             return a.first < b.first;
         });

    vector<int> result;
    for (const auto &[num, _] : sortOrder)
    {
        result.push_back(num);
    }

    return result;
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

    while (getline(input_file, line, '\n'))
    {
        if (line.empty())
        {
            lineType = UPDATE;
        }

        if (lineType == RULE)
        {
            vector<int> rule;
            vector<string> splitLine = split(line, '|');
            for (string token : splitLine)
            {
                int parsedToken = stoi(token);
                rule.push_back(parsedToken);
            }
            rules.push_back(rule);
        }
        else
        {
            vector<int> update;
            vector<string> splitLine = split(line, ',');
            for (string token : splitLine)
            {
                int parsedToken = stoi(token);
                update.push_back(parsedToken);
            }
            updates.push_back(update);
        }
    }

    vector<vector<int>> invalidUpdates;

    for (auto update : updates)
    {
        bool valid = isValidUpdate(rules, update);
        if (!valid)
        {
            invalidUpdates.push_back(update);
        }
    }

    for (const auto &update : invalidUpdates)
    {
        if (!update.empty())
        {
            vector<int> fixedOrder = fixOrder(rules, update);
            answer += fixedOrder[update.size() / 2];
        }
    }

    cout << "Answer: " << answer << endl;

    input_file.close();

    return 0;
}