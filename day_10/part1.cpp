#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*
| is N-S
- is E-W
L is N-E
J is N-W
7 is S-W
F is S-E
*/

set<char> newSet({'N', 'S', 'E', 'W'});

struct Pipe {
    char ch;
    set<char> connections;

    Pipe(char in) {
        ch = in;
        switch (in) {
            case 'S':
                connections = {'N', 'S', 'E', 'W'};
                break;

            case '|':
                connections = {'N', 'S'};
                break;
            case '-':
                connections = {'E', 'W'};
                break;
            case 'L':
                connections = {'N', 'E'};
                break;
            case 'J':
                connections = {'N', 'W'};
                break;
            case '7':
                connections = {'S', 'W'};
                break;
            case 'F':
                connections = {'S', 'E'};
                break;
            default:
                break;
        }
    }
};

set<char> getConnections(char in);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int x = 0;
    int y = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines.size(); j++) {
            if (lines[i][j] == 'S') {
                x = j;
                y = i;
                goto omg;
            }
        }
    }
omg:
    char pos = '.';
    int step = 0;
    int lastX = 0;
    int lastY = 0;
    int sCount = 0;
    while (pos != 'S' || sCount != 2) {
        pos = lines[y][x];
        if (pos == 'S') {
            sCount++;
        }
        for (char dir : getConnections(pos)) {
            if (dir == 'N') {
                set<char> conSet = getConnections(lines[y - 1][x]);
                if (conSet.find('S') != conSet.end() && !(lastY == (y - 1) && lastX == (x))) {
                    lastX = x;
                    lastY = y--;
                    step++;
                    break;
                }
            }
            if (dir == 'S') {
                set<char> conSet = getConnections(lines[y + 1][x]);
                if (conSet.find('N') != conSet.end() && !(lastY == (y + 1) && lastX == (x))) {
                    lastX = x;
                    lastY = y++;
                    step++;
                    break;
                }
            }
            if (dir == 'E') {
                set<char> conSet = getConnections(lines[y][x + 1]);
                if (conSet.find('W') != conSet.end() && !(lastY == (y) && lastX == (x + 1))) {
                    lastX = x++;
                    lastY = y;
                    step++;
                    break;
                }
            }
            if (dir == 'W') {
                set<char> conSet = getConnections(lines[y][x - 1]);
                if (conSet.find('E') != conSet.end() && !(lastY == (y) && lastX == (x - 1))) {
                    lastX = x--;
                    lastY = y;
                    step++;
                    break;
                }
            }
        }
    }
    cout << step / 2;
}

set<char> getConnections(char in) {
    set<char> connections;
    switch (in) {
        case 'S':
            connections = {'N', 'S', 'E', 'W'};
            break;
        case '|':
            connections = {'N', 'S'};
            break;
        case '-':
            connections = {'E', 'W'};
            break;
        case 'L':
            connections = {'N', 'E'};
            break;
        case 'J':
            connections = {'N', 'W'};
            break;
        case '7':
            connections = {'S', 'W'};
            break;
        case 'F':
            connections = {'S', 'E'};
            break;
        default:
            connections = {};
            break;
    }
    return connections;
}