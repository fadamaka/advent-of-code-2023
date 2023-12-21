#include <..\utils\aoc.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> stepDivisors;

vector<string> lines;
vector<vector<int>> weights;

int steps = 1600;

bool dividable(int n) {
    for (auto &&i : stepDivisors) {
        if (n % i == 0)
            return true;
    }
    return false;
}

void oUpdate(int y, int x, int counter) {
    if (counter <= steps) {
        weights[y][x] = counter;
        counter++;
        if ((y - 1) >= 0) {
            if (lines[y - 1][x] == '.' && weights[y - 1][x] > counter) {
                oUpdate(y - 1, x, counter);
            }
        }
        if ((y + 1) < lines.size()) {
            if (lines[y + 1][x] == '.' && weights[y + 1][x] > counter) {
                oUpdate(y + 1, x, counter);
            }
        }

        if ((x - 1) >= 0) {
            if (lines[y][x - 1] == '.' && weights[y][x - 1] > counter) {
                oUpdate(y, x - 1, counter);
            }
        }
        if ((x + 1) < lines[y].size()) {
            if (lines[y][x + 1] == '.' && weights[y][x + 1] > counter) {
                oUpdate(y, x + 1, counter);
            }
        }
    }
}

int main() {
    lines = readFileIntoVector("big-data3.txt");

    int y = 0;
    int x = 0;

    for (size_t i = 0; i < lines.size(); i++) {
        vector<int> v;
        weights.push_back(v);
        for (size_t j = 0; j < lines[i].size(); j++) {
            weights[i].push_back(INT_MAX);
            if (lines[i][j] == 'S') {
                y = i;
                x = j;
            }
        }
    }
    lines[y][x] = '.';
    oUpdate(y, x, 0);
    int result = 0;
    int mdResult = 0;
    int rockCount = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '.' && (abs(i - y) + abs(j - x)) <= steps && (abs(i - y) + abs(j - x)) % 2 == steps % 2) {
                mdResult++;
            }

            if (lines[i][j] == '#' && (abs(i - y) + abs(j - x)) <= steps && (abs(i - y) + abs(j - x)) % 2 == steps % 2) {
                rockCount++;
            }
        }
    }

    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (weights[i][j] != INT_MAX && weights[i][j] % 2 == steps % 2) {
                result++;
                lines[i][j] = 'O';
            }
        }
    }
    for (x = 65; x < 1601; x = x + 131) {
        int localResult = 0;
        for (size_t i = 0; i < lines.size(); i++) {
            for (size_t j = 0; j < lines[i].size(); j++) {
                if (weights[i][j] != INT_MAX && weights[i][j] <= x && weights[i][j] % 2 == x % 2) {
                    localResult++;
                }
            }
        }
        cout << x << " " << localResult << endl;
    }

    // for (size_t i = 0; i < lines.size(); i++) {
    //     for (size_t j = 0; j < lines[i].size(); j++) {
    //         cout << lines[i][j];
    //     }
    //     cout << endl;
    // }
    cout << endl;
    cout << result << endl;
    cout << mdResult << endl;
    cout << (((steps + 1) * 2) * (steps + 1)) / 2 - rockCount << endl;
}