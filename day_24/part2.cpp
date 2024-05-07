#include <..\utils\aoc.h>

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

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    TDPoint p = TDPoint(1L, 1L, 1L, 2L, 3L, -4L);
    TDPoint p2 = TDPoint(3L, 3L, 3L, 2L, 3L, -4L);
    TDPoint p4 = TDPoint(0L, 0L, 4L, 2L, 3L, -4L);
    TDPoint p3 = p - p2;
    TDPoint p5 = p4 - p2;
    cout << "p:" << p << endl;
    cout << "p2:" << p2 << endl;
    cout << "p3:" << p3 << endl;
    cout << "p4:" << p4 << endl;
    cout << "p5:" << p5 << endl;
    p5.increment(1);
    cout << "p6:" << p5 << endl;

    cout << "before: " << p << endl;
    p.increment(1);
    cout << "after: " << p << endl;
    p.increment(2);
    cout << "after2: " << p << endl;

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

    for (auto&& i : v) {
        cout << i << endl;
    }

    vector<map<tuple<long long, long long, long long>, TDPoint>> timeVector;
    for (size_t i = 0; i <= v.size(); i++) {
        map<tuple<long long, long long, long long>, TDPoint> fv;
        for (auto&& e : v) {
            TDPoint element = e;
            element.increment(i);
            fv.insert(pair<tuple<long long, long long, long long>, TDPoint>(tuple<long long, long long, long long>(element.x, element.y, element.z), element));
        }
        timeVector.push_back(fv);
    }
    int counter = 0;
    for (auto&& v : timeVector) {
        cout << counter++ << endl;
        for (auto&& i : v) {
            cout << i.second << endl;
        }
    }

    for (auto&& i : timeVector[1]) {
        for (auto&& j : timeVector[2]) {
            TDPoint k = i.second - j.second;
            k.increment(2);
            if (timeVector[3].find(tuple<long long, long long, long long>(k.x, k.y, k.z)) != timeVector[3].end()) {
                cout << "1: " << i.second << endl;
                cout << "2: " << j.second << endl;
                cout << "3: " << timeVector[3].find(tuple<long long, long long, long long>(k.x, k.y, k.z))->second << endl;
                cout << "k: " << k << endl;
            } else {
                cout << "no match" << endl;
            }
        }
    }
}