#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool checkNeighbour(vector<string> lines, int i, int j);
int getNumber(string line, int j);
int skipAhead(string line, int j);
bool isInt(char chr);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            // cout << lines[i][j];
            int charAsInt = int(lines[i][j]);
            if (isInt(lines[i][j])) {
                if (checkNeighbour(lines, i, j)) {
                    sum += getNumber(lines[i], j);
                    // cout << "found number: " << getNumber(lines[i], j) << endl;
                    j = skipAhead(lines[i], j);
                }
            }
        }
        // cout << endl;
    }

    cout << "result: " << sum << endl;
}

bool checkNeighbour(vector<string> lines, int i, int j) {
    /*
    ###
    #N#
    ##T
    */
    if (i + 1 < lines.size() && j + 1 < lines[i].size()) {
        if (!isInt(lines[i + 1][j + 1]) && lines[i + 1][j + 1] != '.') {
            return true;
        }
    }
    /*
    T##
    #N#
    ###
    */
    if (i - 1 >= 0 && j - 1 >= 0) {
        if (!isInt(lines[i - 1][j - 1]) && lines[i - 1][j - 1] != '.') {
            return true;
        }
    }

    /*
    ###
    #N#
    T##
    */
    if (i + 1 < lines.size() && j - 1 >= 0) {
        if (!isInt(lines[i + 1][j - 1]) && lines[i + 1][j - 1] != '.') {
            return true;
        }
    }
    /*
    ##T
    #N#
    ###
    */
    if (i - 1 >= 0 && j + 1 < lines[i].size()) {
        if (!isInt(lines[i - 1][j + 1]) && lines[i - 1][j + 1] != '.') {
            return true;
        }
    }
    /*
    #T#
    #N#
    ###
    */
    if (i - 1 >= 0) {
        if (!isInt(lines[i - 1][j]) && lines[i - 1][j] != '.') {
            return true;
        }
    }
    /*
    ###
    #N#
    #T#
    */
    if (i + 1 < lines.size()) {
        if (!isInt(lines[i + 1][j]) && lines[i + 1][j] != '.') {
            return true;
        }
    }
    /*
    ###
    #NT
    ###
    */
    if (j + 1 < lines[i].size()) {
        if (!isInt(lines[i][j + 1]) && lines[i][j + 1] != '.') {
            return true;
        }
    }
    /*
    ###
    TN#
    ###
    */
    if (j - 1 >= 0) {
        if (!isInt(lines[i][j - 1]) && lines[i][j - 1] != '.') {
            return true;
        }
    }

    return false;
}
int getNumber(string line, int j) {
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
                break;
            }
        }
    }

    return stoi(strNum);
}
int skipAhead(string line, int j) {
    int i = j;
    while (i < line.size() && isInt(line[i])) {
        i++;
    }
    return i - 1;
}

bool isInt(char chr) {
    if (47 < int(chr) && int(chr) < 58) {
        return true;
    } else {
        return false;
    }
}