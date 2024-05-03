#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum axis {
    X,
    Y,
    Z,
    O
};

struct Coord {
    int x;
    int y;
    int z;

    Coord(int xIn, int yIn, int zIn) {
        x = xIn;
        y = yIn;
        z = zIn;
    }
    Coord(){};
};
struct Brick {
    Coord start;
    Coord end;
    axis ax;
    int length;
    vector<Brick*> above;
    vector<Brick*> below;
    Brick(Coord sIn, Coord eIn, axis aIn, int iLen) {
        start = sIn;
        end = eIn;
        ax = aIn;
        length = iLen;
    }
    Brick(){};
};
ostream& operator<<(ostream& os, const Coord& coord) {
    os << coord.x
       << ","
       << coord.y
       << ","
       << coord.z;
    return os;
}
ostream& operator<<(ostream& os, const axis& ax) {
    string str = ax == X ? "X" : ax == Y ? "Y"
                                         : "Z";
    os << str;
    return os;
}
ostream& operator<<(ostream& os, const Brick& brick) {
    os << brick.start
       << "~"
       << brick.end
       << "->"
       << brick.ax
       << " len: "
       << brick.length;
    return os;
}

Brick* lineToBrick(string line);
axis determineAxis(Coord start, Coord end);

main() {
    vector<string> lines = readFileIntoVector("test-data.txt");
    vector<Brick*> bricks;

    transform(lines.begin(), lines.end(), back_inserter(bricks), [](const string& str) { return lineToBrick(str); });
    for (auto&& i : bricks) {
        cout << *i << endl;
    }
}
Brick* lineToBrick(string line) {
    vector<string> split = splitByChar(line, '~');
    vector<string> start = splitByChar(split[0], ',');
    vector<string> end = splitByChar(split[1], ',');

    Coord startC = Coord(stoi(start[0]), stoi(start[1]), stoi(start[2]));
    Coord endC = Coord(stoi(end[0]), stoi(end[1]), stoi(end[2]));
    axis ax = determineAxis(startC, endC);

    int len = 0;
    if (ax == X) {
        len = endC.x - startC.x;
    }
    if (ax == Y) {
        len = endC.y - startC.y;
    }
    if (ax == Z) {
        len = endC.z - startC.z;
    }
    len += 1;

    return new Brick(startC,
                     endC,
                     ax, len);
}
axis determineAxis(Coord start, Coord end) {
    if (start.x != end.x) {
        return X;
    }
    if (start.y != end.y) {
        return Y;
    }
    if (start.z != end.z) {
        return Z;
    }
    return O;
};