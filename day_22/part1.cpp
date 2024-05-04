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
                             : ax == Z   ? "Z"
                                         : "O";
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
bool onSegment(Coord p, Coord q, Coord r);
int orientation(Coord p, Coord q, Coord r);
bool doIntersect(Coord p1, Coord q1, Coord p2, Coord q2);
bool brickIntersect(Brick brickA, Brick brickB);
bool compareByZ(Brick* a, Brick* b) {
    return a->start.z < b->start.z;
}

bool compareByZnX(Brick* a, Brick* b) {
    if (a->start.z == b->start.z) {
        if (a->start.x == b->start.x) {
            return a->start.y < b->start.y;
        }
        return a->start.x < b->start.x;
    }
    return a->start.z < b->start.z;
}

main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<Brick*> unsortedBricks;
    vector<Brick*> bricks;

    transform(lines.begin(), lines.end(), back_inserter(unsortedBricks), [](const string& str) { return lineToBrick(str); });
    transform(lines.begin(), lines.end(), back_inserter(bricks), [](const string& str) { return lineToBrick(str); });
    sort(bricks.begin(), bricks.end(), compareByZ);

    // for (auto&& i : bricks) {
    //     cout << *i << endl;
    // }

    // take first brick and put to Z=1
    bricks[0]->start.z = 1;
    bricks[0]->end.z = 1;
    // or just do a 2d array with Z as index and check intersections, when there is an intersection halt brick at Z=1
    vector<vector<Brick*>> layers{vector<Brick*>{bricks[0]}};
    // for (auto&& i : bricks) {
    //     cout << *i << endl;
    // }
    // bricks.erase(bricks.begin());
    bool first = true;
    for (auto&& i : bricks) {
        if (first) {
            first = false;
            continue;
        }
        bool intersects = false;
        for (long j = layers.size() - 1; j >= 0; j--) {
            for (auto&& k : layers[j]) {
                if (brickIntersect(*i, *k)) {
                    intersects = true;
                    k->above.push_back(i);
                    i->below.push_back(k);
                }
            }
            if (intersects) {
                if (layers.size() == j + 1) {
                    layers.push_back(vector<Brick*>());
                }
                if (i->ax == Z) {
                    while ((j + i->length) >= layers.size()) {
                        layers.push_back(vector<Brick*>());
                    }
                    i->start.z = j + 2;
                    i->end.z = j + 1 + i->length;
                    layers[j + i->length].push_back(i);
                } else {
                    i->start.z = j + 2;
                    i->end.z = j + 2;
                    layers[j + 1].push_back(i);
                }
                break;
            }
        }
        if (!intersects) {
            i->start.z = 1;

            if (i->ax != Z) {
                i->end.z = 1;
                layers[0].push_back(i);
            } else {
                i->end.z = i->length;

                while ((i->length - 1) >= layers.size()) {
                    layers.push_back(vector<Brick*>());
                }
                layers[i->length - 1].push_back(i);
            }
        }
    }

    // cout << layers.size() << endl;

    // cout << brickIntersect(*bricks[1], *bricks[2]) << endl;
    //

    // for (auto&& i : layers) {
    //     cout << endl;
    //     for (auto&& j : i) {
    //         cout << *j << endl;
    //     }
    // }
    // cout << endl;
    int disCount = 0;
    int zMax = 0;

    sort(bricks.begin(), bricks.end(), compareByZnX);
    for (auto&& i : bricks) {
        if (i->start.z > 0) {
            zMax = i->start.z;
        }
        bool distintFlag = false;
        if (i->above.size() == 0) {
            distintFlag = true;
        }
        for (auto&& j : i->above) {
            if (j->below.size() > 1) {
                distintFlag = true;
            } else {
                distintFlag = false;
                break;
            }
        }
        if (distintFlag) {
            disCount++;
        }
        // string str = distintFlag ? "TRUE" : "FALSE";
        // cout << *i << " dis:" << str << " a:" << i->above.size() << " b:" << i->below.size() << endl;
    }
    // cout << endl;
    cout << "result:" << disCount << endl;
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

bool onSegment(Coord p, Coord q, Coord r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Coord p, Coord q, Coord r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-Coords/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear

    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Coord p1, Coord q1, Coord p2, Coord q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;  // Doesn't fall in any of the above cases
}

bool brickIntersect(Brick a, Brick b) {
    return doIntersect(a.start, a.end, b.start, b.end);
}