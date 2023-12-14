#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

pair<string, vector<int>> inputParser(string str, int j) {
    vector<string> spaceSplit = splitByChar(str, ' ');
    vector<int> validatorNumbers;
    vector<string> validatorNumbersStr = splitByChar(spaceSplit[1], ',');
    transform(validatorNumbersStr.begin(), validatorNumbersStr.end(), back_inserter(validatorNumbers), [](const string& str) { return stoi(str); });
    string pt2 = spaceSplit[0];
    vector<int> validatorNumbersPt2 = validatorNumbers;
    for (int i = 0; i < j; i++) {
        pt2 += '?' + spaceSplit[0];
        validatorNumbersPt2.insert(validatorNumbersPt2.end(), validatorNumbers.begin(), validatorNumbers.end());
    }

    return pair<string, vector<int>>(pt2, validatorNumbersPt2);
}

unsigned long long int solve(string springs, vector<int> groups, map<pair<int, vector<int>>, unsigned long long int>& cache, int i) {
    unsigned long long int result = 0ULL;
    if (groups.size() == 0) {
        if (springs.size() > i && springs.substr(i).find('#') != string::npos) {
            return 0ULL;
        } else {
            return 1ULL;
        }
    }
    while (i < springs.size() && springs[i] != '#' && springs[i] != '?') {
        i++;
    }
    if (i > springs.size()) {
        return 0ULL;
    }
    if (cache.count(pair<int, vector<int>>(i, groups)) > 0) {
        return cache.find(pair<int, vector<int>>(i, groups))->second;  // i num groups
    }
    if (springs.size() >= (i + groups[0]) && springs.substr(i, groups[0]).find('.') == string::npos && (i + groups[0] >= springs.size() || springs[i + groups[0]] == '.' || springs[i + groups[0]] == '?')) {
        vector<int> v(groups.begin() + 1, groups.end());
        unsigned long long subresult = solve(springs, v, cache, i + groups[0] + 1);
        result += subresult;
    }
    if (springs[i] == '?') {
        result += solve(springs, groups, cache, i + 1);
    }
    cache.insert(pair<pair<int, vector<int>>, unsigned long long int>(pair<int, vector<int>>(i, groups), result));
    return result;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<pair<string, vector<int>>> parsedLines;
    transform(lines.begin(), lines.end(), back_inserter(parsedLines), [](const string& str) { return inputParser(str, 4); });
    unsigned long long int result = 0;
    for (pair<string, vector<int>> p : parsedLines) {
        map<pair<int, vector<int>>, unsigned long long int> cache;
        result += solve(p.first, p.second, cache, 0);
    }

    cout << result << endl;
}