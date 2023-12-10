#include <..\utils\aoc.h>

#include <iostream>
#include <map>
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

set<char> getConnections(char in);
void markInAndOut(char outsideX, char outsideY, int y, int x);
vector<string> newPlane;
string updateOutside(char from, char to, char outsideY, char outsideX);
void oUpdate(int y, int x);

int main() {
    int x = 0;
    int y = 0;
    vector<string> lines = readFileIntoVector("data.txt");
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

    for (int i = 0; i < lines.size(); i++) {
        newPlane.push_back("");
        for (int j = 0; j < lines.size(); j++) {
            newPlane[i] += '.';
        }
    }

    int step = 0;
    int lastX = 0;
    int lastY = 0;
    int sCount = 0;
    int highestX = 0;
    int highestY = 0;
    int lowestX = 150;
    int lowestY = 150;
    // first looping
    char pos = '.';
    while (pos != 'S' || sCount != 2) {
        pos = lines[y][x];
        newPlane[y][x] = pos;
        if (highestX < x) {
            highestX = x;
        }
        if (highestY < y) {
            highestY = y;
        }
        if (lowestX > x) {
            lowestX = x;
        }
        if (lowestY > y) {
            lowestY = y;
        }
        if (pos == 'S') {
            newPlane[y][x] = '7';
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
    cout << "pt2 " << step / 2 << endl;
    cout << "lowestX: " << lowestX << endl;
    cout << "lowestY: " << lowestY << endl;
    cout << "highestX: " << highestX << endl;
    cout << "highestY: " << highestY << endl;

    for (int i = 0; i < newPlane.size(); i++) {
        for (int j = 0; j < newPlane.size(); j++) {
            cout << newPlane[i][j];
        }
        cout << endl;
    }

    // second looping
    map<pair<int, int>, bool> visited;
    // coords of an outside | pipe
    x = 91;
    y = 1;
    pos = '.';
    char outsideX = '-';
    char outsideY = 'X';
    char from = 'S';
    char to = 'N';
    int count2 = 0;
    while (visited.count(pair<int, int>(y, x)) == 0) {
        pos = newPlane[y][x];
        markInAndOut(outsideY, outsideX, y, x);

        visited.insert(pair<pair<int, int>, bool>(pair<int, int>(y, x), true));
        for (char dir : getConnections(pos)) {
            if (dir == 'N') {
                set<char> conSet = getConnections(newPlane[y - 1][x]);
                if (conSet.find('S') != conSet.end() && !(lastY == (y - 1) && lastX == (x))) {
                    lastX = x;
                    lastY = y--;
                    step++;
                    break;
                }
            }
            if (dir == 'S') {
                set<char> conSet = getConnections(newPlane[y + 1][x]);
                if (conSet.find('N') != conSet.end() && !(lastY == (y + 1) && lastX == (x))) {
                    lastX = x;
                    lastY = y++;
                    step++;
                    break;
                }
            }
            if (dir == 'E') {
                set<char> conSet = getConnections(newPlane[y][x + 1]);
                if (conSet.find('W') != conSet.end() && !(lastY == (y) && lastX == (x + 1))) {
                    lastX = x++;
                    lastY = y;
                    step++;
                    break;
                }
            }
            if (dir == 'W') {
                set<char> conSet = getConnections(newPlane[y][x - 1]);
                if (conSet.find('E') != conSet.end() && !(lastY == (y) && lastX == (x - 1))) {
                    lastX = x--;
                    lastY = y;
                    step++;
                    break;
                }
            }
        }
        from = newPlane[lastY][lastX];
        to = newPlane[y][x];
        string update = updateOutside(from, to, outsideY, outsideX);
        outsideY = update[0];
        outsideX = update[1];
    }

    cout << endl;

    for (int i = 0; i < newPlane.size(); i++) {
        for (int j = 0; j < newPlane.size(); j++) {
            cout << newPlane[i][j];
        }
        cout << endl;
    }

    // map<pair<int, int>, bool> visited2;
    // x = 91;
    // y = 1;
    // pos = '.';
    // count2 = 0;
    // while (visited2.count(pair<int, int>(y, x)) == 0) {
    //     pos = newPlane[y][x];
    //     count2++;
    //     int poz = count2 % 10;
    //     newPlane[y][x] = char(poz + 48);

    //     visited2.insert(pair<pair<int, int>, bool>(pair<int, int>(y, x), true));
    //     for (char dir : getConnections(pos)) {
    //         if (dir == 'N') {
    //             set<char> conSet = getConnections(newPlane[y - 1][x]);
    //             if (conSet.find('S') != conSet.end() && !(lastY == (y - 1) && lastX == (x))) {
    //                 lastX = x;
    //                 lastY = y--;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'S') {
    //             set<char> conSet = getConnections(newPlane[y + 1][x]);
    //             if (conSet.find('N') != conSet.end() && !(lastY == (y + 1) && lastX == (x))) {
    //                 lastX = x;
    //                 lastY = y++;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'E') {
    //             set<char> conSet = getConnections(newPlane[y][x + 1]);
    //             if (conSet.find('W') != conSet.end() && !(lastY == (y) && lastX == (x + 1))) {
    //                 lastX = x++;
    //                 lastY = y;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'W') {
    //             set<char> conSet = getConnections(newPlane[y][x - 1]);
    //             if (conSet.find('E') != conSet.end() && !(lastY == (y) && lastX == (x - 1))) {
    //                 lastX = x--;
    //                 lastY = y;
    //                 step++;
    //                 break;
    //             }
    //         }
    //     }
    // }
    // cout << endl;

    // for (int i = 0; i < newPlane.size(); i++) {
    //     for (int j = 0; j < newPlane.size(); j++) {
    //         cout << newPlane[i][j];
    //     }
    //     cout << endl;
    // }

    // newPlane = readFileIntoVector("test.txt");

    // map<pair<int, int>, bool> visited3;
    // x = 4;
    // y = 2;
    // pos = '.';
    // outsideX = '-';
    // outsideY = 'X';
    // from = 'S';
    // to = 'N';
    // while (visited3.count(pair<int, int>(y, x)) == 0) {
    //     pos = newPlane[y][x];
    //     markInAndOut(outsideY, outsideX, y, x);

    //     visited3.insert(pair<pair<int, int>, bool>(pair<int, int>(y, x), true));
    //     for (char dir : getConnections(pos)) {
    //         if (dir == 'N') {
    //             set<char> conSet = getConnections(newPlane[y - 1][x]);
    //             if (conSet.find('S') != conSet.end() && !(lastY == (y - 1) && lastX == (x))) {
    //                 lastX = x;
    //                 lastY = y--;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'S') {
    //             set<char> conSet = getConnections(newPlane[y + 1][x]);
    //             if (conSet.find('N') != conSet.end() && !(lastY == (y + 1) && lastX == (x))) {
    //                 lastX = x;
    //                 lastY = y++;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'E') {
    //             set<char> conSet = getConnections(newPlane[y][x + 1]);
    //             if (conSet.find('W') != conSet.end() && !(lastY == (y) && lastX == (x + 1))) {
    //                 lastX = x++;
    //                 lastY = y;
    //                 step++;
    //                 break;
    //             }
    //         }
    //         if (dir == 'W') {
    //             set<char> conSet = getConnections(newPlane[y][x - 1]);
    //             if (conSet.find('E') != conSet.end() && !(lastY == (y) && lastX == (x - 1))) {
    //                 lastX = x--;
    //                 lastY = y;
    //                 step++;
    //                 break;
    //             }
    //         }
    //     }
    //     from = newPlane[lastY][lastX];
    //     to = newPlane[y][x];
    //     string update = updateOutside(from, to, outsideY, outsideX);
    //     outsideY = update[0];
    //     outsideX = update[1];
    // }

    // cout << endl;

    // for (int i = 0; i < newPlane.size(); i++) {
    //     for (int j = 0; j < newPlane[i].size(); j++) {
    //         cout << newPlane[i][j];
    //     }
    //     cout << endl;
    // }
    int resultCount = 0;
    for (int i = 0; i < newPlane.size(); i++) {
        for (int j = 0; j < newPlane[i].size(); j++) {
            if (newPlane[i][j] == '.') {
                resultCount++;
            }
        }
    }
    cout << resultCount;
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

void markInAndOut(char outsideY, char outsideX, int y, int x) {
    if (outsideY == '-' && (y - 1) >= 0) {
        if (newPlane[y - 1][x] == '.') {
            oUpdate(y - 1, x);
        }
    }
    if (outsideY == '+' && (y + 1) < newPlane.size()) {
        if (newPlane[y + 1][x] == '.') {
            oUpdate(y + 1, x);
        }
    }

    if (outsideX == '-' && (x - 1) >= 0) {
        if (newPlane[y][x - 1] == '.') {
            oUpdate(y, x - 1);
        }
    }
    if (outsideX == '+' && (x + 1) < newPlane[y].size()) {
        if (newPlane[y][x + 1] == '.') {
            oUpdate(y, x + 1);
        }
    }
}

string updateOutside(char from, char to, char outsideY, char outsideX) {
    char newOutsideY = outsideY;
    char newOutsideX = outsideX;
    string result = "";
    char turn = 'N';
    if (from == '|' && to == 'F') {
        turn = 'R';
        if (outsideX == '+') {
            newOutsideX = '+';
            newOutsideY = '+';
        } else {
            if (outsideX == '-') {
                newOutsideX = '-';
                newOutsideY = '-';
            }
        }
    }
    if (from == '|' && to == '7') {
        turn = 'L';
        if (outsideX == '+') {
            newOutsideX = '+';
            newOutsideY = '-';
        } else {
            if (outsideX == '-') {
                newOutsideX = '-';
                newOutsideY = '+';
            }
        }
    }
    if (from == '|' && to == 'J') {
        turn = 'R';
        if (outsideX == '+') {
            newOutsideX = '+';
            newOutsideY = '+';
        } else {
            if (outsideX == '-') {
                newOutsideX = '-';
                newOutsideY = '-';
            }
        }
    }
    if (from == '|' && to == 'L') {
        turn = 'L';
        if (outsideX == '+') {
            newOutsideX = '+';
            newOutsideY = '-';
        } else {
            if (outsideX == '-') {
                newOutsideX = '-';
                newOutsideY = '+';
            }
        }
    }

    if (from == '-' && to == '7') {
        turn = 'R';
        if (outsideY == '+') {
            newOutsideY = '+';
            newOutsideX = '-';
        } else {
            if (outsideY == '-') {
                newOutsideY = '-';
                newOutsideX = '+';
            }
        }
    }
    if (from == '-' && to == 'J') {
        turn = 'L';
        if (outsideY == '+') {
            newOutsideY = '+';
            newOutsideX = '+';
        } else {
            if (outsideY == '-') {
                newOutsideY = '-';
                newOutsideX = '-';
            }
        }
    }
    if (from == '-' && to == 'L') {
        turn = 'R';
        if (outsideY == '+') {
            newOutsideY = '+';
            newOutsideX = '-';
        } else {
            if (outsideY == '-') {
                newOutsideY = '-';
                newOutsideX = '+';
            }
        }
    }
    if (from == '-' && to == 'F') {
        turn = 'L';
        if (outsideY == '+') {
            newOutsideY = '+';
            newOutsideX = '+';
        } else {
            if (outsideY == '-') {
                newOutsideY = '-';
                newOutsideX = '-';
            }
        }
    }
    // F

    if (from == 'F' && to == '-') {
        newOutsideX = 'X';
    }
    if (from == 'F' && to == '7') {
        if (newOutsideX == '+') {
            newOutsideX = '-';
        } else {
            if (newOutsideX == '-') {
                newOutsideX = '+';
            }
        }
    }
    if (from == 'F' && to == 'J') {
        // if (newOutsideY == '+') {
        //     newOutsideY = '-';
        // }
        // if (newOutsideY == '-') {
        //     newOutsideY = '+';
        // }
    }
    if (from == 'F' && to == 'L') {
        if (newOutsideY == '+') {
            newOutsideY = '-';
        } else {
            if (newOutsideY == '-') {
                newOutsideY = '+';
            }
        }
    }

    if (from == 'F' && to == '|') {
        newOutsideY = 'X';
    }
    // L

    if (from == 'L' && to == '-') {
        newOutsideX = 'X';
    }
    if (from == 'L' && to == 'J') {
        if (newOutsideX == '+') {
            newOutsideX = '-';
        } else {
            if (newOutsideX == '-') {
                newOutsideX = '+';
            }
        }
    }
    if (from == 'L' && to == '7') {
        // if (newOutsideY == '+') {
        //     newOutsideY = '-';
        // }
        // if (newOutsideY == '-') {
        //     newOutsideY = '+';
        // }
    }

    if (from == 'L' && to == 'F') {
        if (newOutsideY == '+') {
            newOutsideY = '-';
        } else {
            if (newOutsideY == '-') {
                newOutsideY = '+';
            }
        }
    }
    // J

    if (from == 'J' && to == '-') {
        newOutsideX = 'X';
    }
    if (from == 'J' && to == 'L') {
        if (newOutsideX == '+') {
            newOutsideX = '-';
        } else {
            if (newOutsideX == '-') {
                newOutsideX = '+';
            }
        }
    }
    if (from == 'J' && to == 'F') {
        // if (newOutsideY == '+') {
        //     newOutsideY = '-';
        // }
        // if (newOutsideY == '-') {
        //     newOutsideY = '+';
        // }
    }

    if (from == 'J' && to == '7') {
        if (newOutsideY == '+') {
            newOutsideY = '-';
        } else {
            if (newOutsideY == '-') {
                newOutsideY = '+';
            }
        }
    }
    // 7

    if (from == '7' && to == '-') {
        newOutsideX = 'X';
    }
    if (from == '7' && to == 'F') {
        if (newOutsideX == '+') {
            newOutsideX = '-';
        } else {
            if (newOutsideX == '-') {
                newOutsideX = '+';
            }
        }
    }
    if (from == '7' && to == 'L') {
        // if (newOutsideY == '+') {
        //     newOutsideY = '-';
        // }
        // if (newOutsideY == '-') {
        //     newOutsideY = '+';
        // }
    }

    if (from == '7' && to == 'J') {
        if (newOutsideY == '+') {
            newOutsideY = '-';
        } else {
            if (newOutsideY == '-') {
                newOutsideY = '+';
            }
        }
    }

    if (from == '7' && to == '|') {
        newOutsideY = 'X';
    }

    return result + newOutsideY + newOutsideX;
}

void oUpdate(int y, int x) {
    newPlane[y][x] = 'O';

    if ((y - 1) >= 0) {
        if (newPlane[y - 1][x] == '.') {
            oUpdate(y - 1, x);
        }
    }
    if ((y + 1) < newPlane.size()) {
        if (newPlane[y + 1][x] == '.') {
            oUpdate(y + 1, x);
        }
    }

    if ((x - 1) >= 0) {
        if (newPlane[y][x - 1] == '.') {
            oUpdate(y, x - 1);
        }
    }
    if ((x + 1) < newPlane[y].size()) {
        if (newPlane[y][x + 1] == '.') {
            oUpdate(y, x + 1);
        }
    }
}