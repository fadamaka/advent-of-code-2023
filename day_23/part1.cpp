#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;

int result = 0;

void oUpdate(int y, int x, int counter, set<pair<int, int>> visited) {
    //^, >, v, and <
    visited.insert(pair<int, int>(y, x));
    if (y == lines.size() - 1 && x == lines[y].size() - 2 && result <= counter) {
        result = counter;
        return;
    }
    counter++;
    if ((y - 1) >= 0) {
        if (visited.find(pair<int, int>(y - 1, x)) == visited.end() && (lines[y - 1][x] == '.' || lines[y - 1][x] == '^')) {
            oUpdate(y - 1, x, counter, visited);
        }
    }
    if ((y + 1) < lines.size()) {
        if (visited.find(pair<int, int>(y + 1, x)) == visited.end() && (lines[y + 1][x] == '.' || lines[y + 1][x] == 'v')) {
            oUpdate(y + 1, x, counter, visited);
        }
    }

    if ((x - 1) >= 0) {
        if (visited.find(pair<int, int>(y, x - 1)) == visited.end() && (lines[y][x - 1] == '.' || lines[y][x - 1] == '<')) {
            oUpdate(y, x - 1, counter, visited);
        }
    }
    if ((x + 1) < lines[y].size()) {
        if (visited.find(pair<int, int>(y, x + 1)) == visited.end() && (lines[y][x + 1] == '.' || lines[y][x + 1] == '>')) {
            oUpdate(y, x + 1, counter, visited);
        }
    }
}

int main() {
    lines = readFileIntoVector("data.txt");

    int y = 0;
    int x = 1;
    oUpdate(y, x, 0, {});
    cout << result << endl;
}