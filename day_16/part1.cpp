#include <..\utils\aoc.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
enum direction {
    N,
    S,
    W,
    E,
    O
};
vector<string> grid;
vector<string> heat;
vector<vector<map<direction, int>>> loop;

void move(int y, int x, direction d) {
    if (loop[y][x][d]++ > 1) {
        return;
    }
    char pos = grid[y][x];
    heat[y][x] = '#';
    direction newD;
    direction split = O;

    switch (pos) {
        case '\\':
            if (d == N) {
                newD = W;
            } else if (d == E) {
                newD = S;
            } else if (d == S) {
                newD = E;
            } else if (d == W) {
                newD = N;
            }

            break;

        case '/':
            if (d == N) {
                newD = E;
            } else if (d == E) {
                newD = N;
            } else if (d == S) {
                newD = W;
            } else if (d == W) {
                newD = S;
            }

            break;

        case '-':
            if (d == N || d == S) {
                newD = E;
                split = W;
            } else {
                newD = d;
            }

            break;

        case '|':
            if (d == E || d == W) {
                newD = S;
                split = N;
            } else {
                newD = d;
            }

            break;

        default:
            newD = d;
            break;
    }
splitjump:
    switch (newD) {
        case N:
            if (y > 0) {
                move(y - 1, x, newD);
            }
            break;

        case W:

            if (x > 0) {
                move(y, x - 1, newD);
            }
            break;
        case E:
            if (x + 1 < grid[y].size()) {
                move(y, x + 1, newD);
            }
            break;

        case S:

            if (y + 1 < grid.size()) {
                move(y + 1, x, newD);
            }
            break;
        default:
            break;
    }
    if (split != O) {
        newD = split;
        split = O;
        goto splitjump;
    }
}

void reset() {
    heat.clear();
    loop.clear();
    for (int i = 0; i < grid.size(); i++) {
        string str;
        vector<map<direction, int>> v;
        for (int j = 0; j < grid[i].size(); j++) {
            map<direction, int> m;
            str += '.';
            m[N] = 0;
            m[S] = 0;
            m[E] = 0;
            m[W] = 0;
            v.push_back(m);
        }
        heat.push_back(str);
        loop.push_back(v);
    }
}

int count() {
    int result = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            // cout << heat[i][j];
            if (heat[i][j] == '#') {
                result++;
            }
        }
        // cout << endl;
    }
    return result;
}
int main() {
    grid = readFileIntoVector("data.txt");
    reset();
    move(0, 0, E);
    int result = count();
    cout << "part1: " << result << endl;
    int newResult = 0;
    for (size_t i = 0; i < grid[0].size(); i++) {
        reset();
        move(0, i, S);
        newResult = count();
        if (newResult > result) {
            result = newResult;
        }
        int y = grid.size() - 1;
        reset();
        move(y, i, N);
        newResult = count();
        if (newResult > result) {
            result = newResult;
        }
    }

    for (size_t i = 0; i < grid.size(); i++) {
        reset();
        move(i, 0, E);
        newResult = count();
        if (newResult > result) {
            result = newResult;
        }
        int y = grid[i].size() - 1;
        reset();
        move(i, y, W);
        newResult = count();
        if (newResult > result) {
            result = newResult;
        }
    }

    cout << "part2: " << result << endl;
}