#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;

int moveUp(int y, int x) {
    if (y - 1 >= 0 && lines[y - 1][x] == '.') {
        return moveUp(y - 1, x);
    } else {
        return y;
    }
}

int main() {
    lines = readFileIntoVector("data.txt");

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'O') {
                int newY = moveUp(i, j);
                if (newY != i) {
                    lines[newY][j] = 'O';
                    lines[i][j] = '.';
                }
            }
        }
    }

    // for (string str : lines) {
    //     for (char ch : str) {
    //         cout << ch;
    //     }
    //     cout << endl;
    // }
    int result = 0;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'O') {
                result += lines.size() - i;
            }
        }
    }
    cout << result;

    /* code */
}