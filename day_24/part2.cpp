#include <..\utils\aoc.h>
#include <Line.h>

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct TDPoint {
    long long x;
    long long y;
    long long z;
    long long xV;
    long long yV;
    long long zV;
    TDPoint(){};
    TDPoint(
        long long x,
        long long y,
        long long z,
        long long xV,
        long long yV,
        long long zV) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->xV = xV;
        this->yV = yV;
        this->zV = zV;
    };

    void increment(long long n) {
        x += (xV * n);
        y += (yV * n);
        z += (zV * n);
    };
    TDPoint operator-(const TDPoint& p) {
        TDPoint difference(x, y, z, p.x - x, p.y - y, p.z - z);
        return difference;
    };
};
ostream& operator<<(ostream& os, const TDPoint& p) {
    os << p.x
       << ", "
       << p.y
       << ", "
       << p.z
       << " @ "
       << p.xV
       << ", "
       << p.yV
       << ", "
       << p.zV;
    return os;
};

long double getDistance(TDPoint a, TDPoint b) {
    return hypotl(hypotl(a.x - b.x, a.y - b.y), a.z - b.z);
}

Vector3 intersect(Line& line1, Line& line2) {
    Vector3 p = line1.point;      // P1
    Vector3 v = line1.direction;  // v
    Vector3 q = line2.point;      // Q1
    Vector3 u = line2.direction;  // u

    // find a = v x u
    Vector3 a = v.cross(u);  // cross product

    // find dot product = (v x u) . (v x u)
    long double dot = a.dot(a);  // inner product

    // if v and u are parallel (v x u = 0), then no intersection, return NaN point
    if (dot == 0)
        return Vector3(NAN, NAN, NAN);

    // find b = (Q1-P1) x u
    Vector3 b = (q - p).cross(u);  // cross product

    // find t = (b.a)/(a.a) = ((Q1-P1) x u) .(v x u) / (v x u) . (v x u)
    long double t = b.dot(a) / dot;

    // find intersection point by substituting t to the line1 eq
    Vector3 point = p + (t * v);
    return point;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<TDPoint> v;

    for (string str : lines) {
        vector<string> firstPlit = splitByChar(str, '@');
        vector<string> point = splitByChar(firstPlit[0], ',');
        vector<string> vector = splitByChar(firstPlit[1], ',');
        long long x = stoll(point[0]);
        long long y = stoll(point[1].substr(1));
        long long z = stoll(point[2].substr(1));

        long long xV = stoll(vector[0]);
        long long yV = stoll(vector[1].substr(1));
        long long zV = stoll(vector[2].substr(1));

        v.push_back(TDPoint(x, y, z, xV, yV, zV));
    }

    // for (auto&& i : v) {
    //     cout << i << endl;
    // }

    // vector<map<tuple<long long, long long, long long>, TDPoint>> timeVector;
    // for (size_t i = 0; i <= v.size(); i++) {
    //     map<tuple<long long, long long, long long>, TDPoint> fv;
    //     for (auto&& e : v) {
    //         TDPoint element = e;
    //         element.increment(i);
    //         fv.insert(pair<tuple<long long, long long, long long>, TDPoint>(tuple<long long, long long, long long>(element.x, element.y, element.z), element));
    //     }
    //     timeVector.push_back(fv);
    // }
    // int counter = 0;
    // for (auto&& v : timeVector) {
    //     cout << counter++ << endl;
    //     for (auto&& i : v) {
    //         cout << i.second << endl;
    //     }
    // }

    // for (auto&& i : timeVector[1]) {
    //     for (auto&& j : timeVector[2]) {
    //         TDPoint k = i.second - j.second;
    //         k.increment(2);
    //         if (timeVector[3].find(tuple<long long, long long, long long>(k.x, k.y, k.z)) != timeVector[3].end()) {
    //             cout << "1: " << i.second << endl;
    //             cout << "2: " << j.second << endl;
    //             cout << "3: " << timeVector[3].find(tuple<long long, long long, long long>(k.x, k.y, k.z))->second << endl;
    //             cout << "k: " << k << endl;
    //         } else {
    //             cout << "no match" << endl;
    //         }
    //     }
    // }
    long double maxDistance = 0L;
    size_t a;
    size_t b;
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            long double distance = getDistance(v[i], v[j]);
            if (distance > maxDistance) {
                maxDistance = distance;
                a = i;
                b = j;
            }
        }
    }
    cout << "distance: " << maxDistance << endl;
    cout << a << ": " << v[a] << endl;
    cout << b << ": " << v[b] << endl;
    TDPoint aV = v[a];
    TDPoint bV = v[b];
    aV.increment(10000000000L);
    bV;
    cout << "distance: " << getDistance(aV, bV) << endl;
    cout << a << ": " << aV << endl;
    cout << b << ": " << bV << endl;

    cout << "5?: " << getDistance(TDPoint(0L, 0L, 0L, 0L, 0L, 0L), TDPoint(3L, 4L, 0L, 0L, 0L, 0L)) << endl;

    Line line1 = Line(Vector3(0L, 10L, 0L), Vector3(0L, 100L, 0L));
    Line line2 = Line(Vector3(8L, 0L, 0L), Vector3(-1L, -2L, 0L));
    cout << intersect(line1, line2) << endl;

    // make line of furthest points

    // loop through all other points
    // check if point intersect with new line
    // look for integer intersect, also check if intersection is in the future

    long long iterations = 10000000L;
    for (long long i = 0; i < iterations; i++) {
        TDPoint iPoint = v[a];
        for (long long j = 0; j < iterations; j++) {
            TDPoint jPoint = v[b];
        }
    }
}