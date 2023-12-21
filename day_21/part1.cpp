#include <..\utils\aoc.h>
#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> stepDivisors;
void primeFactors(int n) {
    while (n % 2 == 0) {
        stepDivisors.push_back(2);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            cout << i << " ";
            n = n / i;
        }
    }
    if (n > 2)

        stepDivisors.push_back(n);
}

vector<string> lines;
vector<vector<int>> weights;

int steps = 64;

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
    lines = readFileIntoVector("data.txt");

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
    lines[y][x] = 'O';
    oUpdate(y, x, 0);
    int result = 0;

    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (weights[i][j] != INT_MAX && weights[i][j] % 2 == 0) {
                result++;
                lines[i][j] = 'O';
            }
        }
    }

    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            cout << lines[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << result << endl;
}