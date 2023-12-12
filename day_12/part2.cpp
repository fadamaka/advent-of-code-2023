#include <..\utils\aoc.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool entryValidator(pair<string, vector<int>> input);
pair<string, vector<int>> inputParser(string str, int j);

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
    transform(lines.begin(), lines.end(), back_inserter(parsedLines), [](const string& str) { return inputParser(str, 0); });

    vector<pair<string, vector<int>>> parsedLinesPt2;
    transform(lines.begin(), lines.end(), back_inserter(parsedLinesPt2), [](const string& str) { return inputParser(str, 1); });

    // for (string str : findBitCombinations(4, 2)) {
    //     cout << str << endl;
    // }
    long long result = 0;

    for (int i = 0; i < parsedLines.size(); i++) {
        pair<string, vector<int>> p = parsedLines[i];
        pair<string, vector<int>> p2 = parsedLinesPt2[i];
        // cout << p.first;
        // for (int i : p.second) {
        //     cout << " " << i;
        // }
        // cout << endl;
        int markCount = countQuestionMarks(p.first);
        int tagCount = countQuestionTags(p.first);
        int countTags = accumulate(p.second.begin(), p.second.end(), 0);
        // cout << "?: " << markCount << endl;
        vector<string> combos = findBitCombinations(markCount, countTags - tagCount);
        // cout << "combinations: " << combos.size() << endl;
        long long valid = 0;
        for (string str : combos) {
            if (entryValidator(pair<string, vector<int>>(replaceMarks(p.first, str), p.second))) {
                valid++;
            }
        }
        int markCount2 = countQuestionMarks(p2.first);
        int tagCount2 = countQuestionTags(p2.first);
        int countTags2 = accumulate(p2.second.begin(), p2.second.end(), 0);
        // cout << "?: " << markCount << endl;
        vector<string> combos2 = findBitCombinations(markCount2, countTags2 - tagCount2);
        cout << i + 1 << " combinations: " << combos2.size() << endl;
        long long valid2 = 0;
        for (string str : combos2) {
            if (entryValidator(pair<string, vector<int>>(replaceMarks(p2.first, str), p2.second))) {
                valid2++;
            }
        }
        long long subresult = valid * pow(valid2 / valid, 4);
        cout << i + 1 << ": " << subresult << endl;
        result += subresult;
        cout << result << endl;
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