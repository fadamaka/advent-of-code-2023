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
}