#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> grid;

enum direction {
    N,
    S,
    W,
    E
};

void move(int y, int x, direction d) {
    char pos = grid[y][x];
    direction newD;
    direction split;

    switch (pos) {
        case '/':
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

        case '\\':
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
            }

            break;

        case '|':
            if (d == E || d == W) {
                newD = S;
                split = N;
            }

            break;

        default:
            break;
    }
}

int main() {
    grid = readFileIntoVector("data.txt");
}