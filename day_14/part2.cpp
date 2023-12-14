#include <..\utils\aoc.h>

#include <cmath>
#include <iostream>
#include <set>
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
int moveLeft(int y, int x) {
    if (x - 1 >= 0 && lines[y][x - 1] == '.') {
        return moveLeft(y, x - 1);
    } else {
        return x;
    }
}
int moveDown(int y, int x) {
    if (y + 1 < lines.size() && lines[y + 1][x] == '.') {
        return moveDown(y + 1, x);
    } else {
        return y;
    }
}
int moveRight(int y, int x) {
    if (x + 1 < lines[y].size() && lines[y][x + 1] == '.') {
        return moveRight(y, x + 1);
    } else {
        return x;
    }
}

int main() {
    lines = readFileIntoVector("data.txt");

    for (string str : lines) {
        for (char ch : str) {
            cout << ch;
        }
        cout << endl;
    }

    cout << endl;

    set<int> cycleSet;

    int cycle = 0;
    int cycleN = 0;

    bool cycleDetected = false;
    long long exitAt = 0;

    for (long long c = 0; c < 10000000000; c++) {
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

        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[i].size(); j++) {
                if (lines[i][j] == 'O') {
                    int newX = moveLeft(i, j);
                    if (newX != j) {
                        lines[i][newX] = 'O';
                        lines[i][j] = '.';
                    }
                }
            }
        }
        for (int i = lines.size() - 1; i >= 0; i--) {
            for (int j = 0; j < lines[i].size(); j++) {
                if (lines[i][j] == 'O') {
                    int newY = moveDown(i, j);
                    if (newY != i) {
                        lines[newY][j] = 'O';
                        lines[i][j] = '.';
                    }
                }
            }
        }

        for (int i = 0; i < lines.size(); i++) {
            for (int j = lines[i].size() - 1; j >= 0; j--) {
                if (lines[i][j] == 'O') {
                    int newX = moveRight(i, j);
                    if (newX != j) {
                        lines[i][newX] = 'O';
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
        if (c > 15000) {
            if (cycle == result && exitAt == 0) {
                cout << "cycle length: " << c - cycleN + 1 << endl;
                exitAt = c - cycleN + 1;
            }
            if (cycleSet.find(result) != cycleSet.end() && !cycleDetected) {
                cout << "cycle detected!" << endl;
                cycle = result;
                cycleDetected = true;
                cycleN = c;
            }
            cycleSet.insert(result);
            if (exitAt != 0 && c % exitAt == 999999999LL % exitAt) {
                cout << "result at 1bill: " << result << endl;
                break;
            }
        }

        cout << "cycle " << c + 1 << " " << result << endl;
    }

    /* code */
}