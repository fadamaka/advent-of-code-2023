#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int getNumbers(vector<string> lines, int i, int j);
string getNumber(int x, string line, int j);
bool isInt(char chr);
vector<string> customSplit(string str);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            // cout << lines[i][j];
            int charAsInt = int(lines[i][j]);
            if (lines[i][j] == '*') {
                sum += getNumbers(lines, i, j);
            }
        }
    }
    cout << "result: " << sum << endl;
    // cout << endl;
}

int getNumbers(vector<string> lines, int i, int j) {
    // cout << "i: " << i << " j: " << j << endl;
    set<string> numbers;
    /*
    ###
    #N#
    ##T
    */
    if (i + 1 < lines.size() && j + 1 < lines[i].size()) {
        if (isInt(lines[i + 1][j + 1])) {
            numbers.insert(getNumber(i + 1, lines[i + 1], j + 1));
        }
    }
    /*
    T##
    #N#
    ###
    */
    if (i - 1 >= 0 && j - 1 >= 0) {
        if (isInt(lines[i - 1][j - 1])) {
            numbers.insert(getNumber(i - 1, lines[i - 1], j - 1));
        }
    }

    /*
    ###
    #N#
    T##
    */
    if (i + 1 < lines.size() && j - 1 >= 0) {
        if (isInt(lines[i + 1][j - 1])) {
            numbers.insert(getNumber(i + 1, lines[i + 1], j - 1));
        }
    }
    /*
    ##T
    #N#
    ###
    */
    if (i - 1 >= 0 && j + 1 < lines[i].size()) {
        if (isInt(lines[i - 1][j + 1])) {
            numbers.insert(getNumber(i - 1, lines[i - 1], j + 1));
        }
    }
    /*
    #T#
    #N#
    ###
    */
    if (i - 1 >= 0) {
        if (isInt(lines[i - 1][j])) {
            numbers.insert(getNumber(i - 1, lines[i - 1], j));
        }
    }
    /*
    ###
    #N#
    #T#
    */
    if (i + 1 < lines.size()) {
        if (isInt(lines[i + 1][j])) {
            numbers.insert(getNumber(i + 1, lines[i + 1], j));
        }
    }
    /*
    ###
    #NT
    ###
    */
    if (j + 1 < lines[i].size()) {
        if (isInt(lines[i][j + 1])) {
            numbers.insert(getNumber(i, lines[i], j + 1));
        }
    }
    /*
    ###
    TN#
    ###
    */
    if (j - 1 >= 0) {
        if (isInt(lines[i][j - 1])) {
            numbers.insert(getNumber(i, lines[i], j - 1));
        }
    }
    if (numbers.size() == 2) {
        set<string>::iterator it = numbers.begin();
        std::advance(it, 0);
        string num1 = *it;
        std::advance(it, 1);
        string num2 = *it;
        // cout << num1 << " * " << num2 << endl;
        // cout << stoi(customSplit(num1)[2]) << " * " << stoi(customSplit(num2)[2]) << endl;
        return stoi(customSplit(num1)[2]) * stoi(customSplit(num2)[2]);
    }
    return 0;
}
string getNumber(int x, string line, int j) {
    string strNum = "";
    for (int i = j; i < line.size(); i++) {
        if (isInt(line[i])) {
            strNum += line[i];
        } else {
            break;
        }
    }
    if (j > 0) {
        for (int i = j - 1; i >= 0; i--) {
            if (isInt(line[i])) {
                strNum = line[i] + strNum;
            } else {
                j = i + 1;
                break;
            }
        }
    }
    return to_string(x) + "|" + to_string(j) + "|" + strNum;
}

bool isInt(char chr) {
    if (47 < int(chr) && int(chr) < 58) {
        return true;
    } else {
        return false;
    }
}

vector<string> customSplit(string str) {
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == '|' || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}