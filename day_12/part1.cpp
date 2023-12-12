#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
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
vector<string> findBitCombinations(int k);

string replaceMarks(string input, string str);
int countQuestionMarks(string str);

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
    // for (string str : findBitCombinations(10)) {
    //     cout << str << endl;
    // }
    int result = 0;

    for (pair<string, vector<int>> p : parsedLines) {
        int markCount = countQuestionMarks(p.first);
        // cout << "?: " << markCount << endl;
        vector<string> combos = findBitCombinations(markCount);
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

vector<string> findBitCombinations(int k) {
    vector<string> DP[K][K];
    string str = "";

    // DP[k][0] will store all k-bit numbers
    // with 0 bits set (All bits are 0's)
    for (int len = 0; len <= k; len++) {
        DP[len][0].push_back(str);
        str = str + ".";
    }

    // fill DP lookup table in bottom-up manner
    // DP[k][n] will store all k-bit numbers
    // with n-bits set
    for (int len = 1; len <= k; len++) {
        for (int n = 1; n <= len; n++) {
            // prefix 0 to all combinations of length len-1
            // with n ones
            for (string str : DP[len - 1][n])
                DP[len][n].push_back("." + str);

            // prefix 1 to all combinations of length len-1
            // with n-1 ones
            for (string str : DP[len - 1][n - 1])
                DP[len][n].push_back("#" + str);
        }
    }

    // print all k-bit binary strings with
    // n-bit set
    vector<string> result;
    string firstResult;

    for (int n = 1; n <= k; n++) {
        firstResult += '.';
        for (string str : DP[k][n]) {
            result.push_back(str);
        }
    }
    result.push_back(firstResult);
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