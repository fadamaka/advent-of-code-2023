#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool entryValidator(pair<string, vector<int>> input);
pair<string, vector<int>> inputParser(string str);

#define K 19

// DP lookup table

// Function to find all combinations k-bit numbers with
// n-bits set where 1 <= n <= k
vector<string> findBitCombinations(int k, int hashtags);

string replaceMarks(string input, string str);
int countQuestionMarks(string str);
int countQuestionTags(string str);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<pair<string, vector<int>>> parsedLines;
    transform(lines.begin(), lines.end(), back_inserter(parsedLines), [](const string& str) { return inputParser(str); });

    // for (pair<string, vector<int>> p : parsedLines) {
    //     if (entryValidator(p)) {
    //         cout << "valid:" << endl;
    //     } else {
    //         cout << "invalid:" << endl;
    //     }
    //     cout << p.first;
    //     for (int i : p.second) {
    //         cout << " " << i;
    //     }
    //     cout << endl;
    // }
    // for (string str : findBitCombinations(4, 2)) {
    //     cout << str << endl;
    // }
    int result = 0;

    for (pair<string, vector<int>> p : parsedLines) {
        int markCount = countQuestionMarks(p.first);
        int tagCount = countQuestionTags(p.first);
        int countTags = accumulate(p.second.begin(), p.second.end(), 0);
        // cout << "?: " << markCount << endl;
        vector<string> combos = findBitCombinations(markCount, countTags - tagCount);
        // cout << "combinations: " << combos.size() << endl;
        int valid = 0;
        for (string str : combos) {
            if (entryValidator(pair<string, vector<int>>(replaceMarks(p.first, str), p.second))) {
                valid++;
            }
        }
        // cout << valid << endl;
        result += valid;
    }
    cout << result;
}

bool entryValidator(pair<string, vector<int>> input) {
    vector<string> springs = splitByChar(input.first, '.');
    set<char> springsCharSet(input.first.begin(), input.first.end());
    if (springsCharSet.find('?') != springsCharSet.end()) {
        cout << "bad input" << endl;
        return false;
    }
    vector<string> filteredSprings;
    copy_if(springs.begin(), springs.end(), back_inserter(filteredSprings), [](const string& str) { return str.size() > 0; });
    if (filteredSprings.size() != input.second.size()) {
        return false;
    }
    for (int i = 0; i < filteredSprings.size(); i++) {
        if (filteredSprings[i].size() != input.second[i]) {
            return false;
        }
    }
    return true;
}

pair<string, vector<int>> inputParser(string str) {
    vector<string> spaceSplit = splitByChar(str, ' ');
    vector<int> validatorNumbers;
    vector<string> validatorNumbersStr = splitByChar(spaceSplit[1], ',');
    transform(validatorNumbersStr.begin(), validatorNumbersStr.end(), back_inserter(validatorNumbers), [](const string& str) { return stoi(str); });
    return pair<string, vector<int>>(spaceSplit[0], validatorNumbers);
}

vector<string> findBitCombinations(int k, int hashtags) {
    string combo;
    vector<string> result;
    for (int i = 0; i < k - hashtags; i++) {
        combo += '.';
    }
    for (int i = 0; i < hashtags; i++) {
        combo += '#';
    }
    result.push_back(combo);

    while (combo.find(".#") != string::npos) {
        int rfound = combo.rfind(".#");
        if (rfound == combo.rfind(".##")) {
            int count = 0;
            for (int i = rfound + 2; i < combo.size(); i++) {
                if (combo[i] == '#') {
                    count++;
                } else {
                    break;
                }
            }
            // cout << combo << " needs to pushback " << count << " #s" << endl;
            if ((rfound + 2 + count) != combo.size()) {
                // cout << "before pb: " << combo << endl;
                // cout << combo.substr(0, rfound + 2) << endl;
                // cout << combo.substr(rfound + 2 + count) << endl;
                // cout << combo.substr(rfound + 2, count) << endl;
                combo = combo.substr(0, rfound + 2) + combo.substr(rfound + 2 + count) + combo.substr(rfound + 2, count);

                // cout << "after pb: " << combo << endl;
            }
        }
        combo.replace(rfound, 2, "#.");
        result.push_back(combo);
    }

    return result;
}

string replaceMarks(string input, string str) {
    int count = 0;
    string newString = input;
    for (int i = 0; i < input.size(); i++) {
        if (newString[i] == '?') {
            newString[i] = str[count];
            count++;
        }
    }
    return newString;
}

int countQuestionMarks(string str) {
    int count = 0;
    for (char ch : str) {
        if (ch == '?') {
            count++;
        }
    }
    return count;
}

int countQuestionTags(string str) {
    int count = 0;
    for (char ch : str) {
        if (ch == '#') {
            count++;
        }
    }
    return count;
}

// string iterateCombo(string input) {
// }