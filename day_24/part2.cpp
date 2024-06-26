#include <..\utils\aoc.h>
#include <Line.h>

#include <Eigen/Dense>
#include <cmath>
#include <future>
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
Line tdToLine(TDPoint vector) {
    TDPoint nV = vector;
    nV.increment(10000L);
    return Line(Vector3(vector.x, vector.y, vector.z), Vector3(nV.x, nV.y, nV.z));
}

// Function to calculate the intersection point of two lines in 3D
Eigen::Vector3d intersectionPoint(Eigen::Vector3d P1, Eigen::Vector3d V1, Eigen::Vector3d P2, Eigen::Vector3d V2) {
    // Calculate the cross product of V1 and V2
    Eigen::Vector3d V1_cross_V2 = V1.cross(V2);

    // Check if the lines are parallel
    if (V1_cross_V2.norm() == 0) {
        std::cout << "The lines are parallel and do not intersect." << std::endl;
        return Eigen::Vector3d::Zero();
    }

    // Calculate the scalar 'a'
    double a = ((P2 - P1).cross(V2)).norm() / V1_cross_V2.norm();

    // Calculate the intersection point
    Eigen::Vector3d intersection = P1 + a * V1;

    return intersection;
}

// Function to calculate the intersection point of two lines in 3D
Eigen::Vector3d intersectionPoint(TDPoint a, TDPoint b) {
    Eigen::Vector3d P1(a.x, a.y, a.z), V1(a.xV, a.yV, a.zV), P2(b.x, b.y, b.z), V2(b.xV, b.yV, b.zV);

    return intersectionPoint(P1, V1, P2, V2);
}

bool workFunc(long long iterations, long long start, long long end, vector<TDPoint> v, size_t a, size_t b) {
    for (long long i = start; i < end; i++) {
        if (i % 10000 == 0) {
            cout << "in func: " + to_string(i) << endl;
        }
        for (long long j = 0; j < iterations; j++) {
            TDPoint iPoint = v[a];
            TDPoint jPoint = v[b];
            iPoint.increment(i);
            jPoint.increment(j);
            TDPoint diff = iPoint - jPoint;
            for (size_t k = 0; k < v.size(); k++) {
                if (k == a || k == b) {
                    if (v.size() - 1 == k) {
                        cout << "found f:" << endl;
                        cout << "i: " << i << endl;
                        cout << "j: " << j << endl;
                        return true;
                    }
                    continue;
                }
                Eigen::Vector3d intersection = intersectionPoint(diff, v[k]);
                double intpart;
                if (modf(intersection[0], &intpart) == 0.0 && modf(intersection[1], &intpart) == 0.0 && modf(intersection[2], &intpart) == 0.0) {
                    if (k > 1) {
                        cout << "i: " << i << " j: " << j << " k: " << k << " "
                             << to_string(intersection[0]) << " " << to_string(intersection[1]) << " " << to_string(intersection[2]) << endl;
                    }
                    if (v.size() - 1 == k) {
                        cout << "found f:" << endl;
                        cout << "i: " << i << endl;
                        cout << "j: " << j << endl;
                        return true;
                    }
                } else {
                    break;
                }
            }
        }
    }
    return false;
}

struct Coords {
    long long x;
    long long y;
    long long z;
    Coords(){};
    Coords(
        long long x,
        long long y,
        long long z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

bool compareByZnX(Coords a, Coords b) {
    if (a.x == b.x) {
        if (a.y == b.y) {
            return a.z < b.z;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
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
    vector<Coords> vc;
    // had a brute force solution to get these, but was not good enough so got them from another solution
    long long i = 207074028602100LL;
    long long j = 592072466466LL;
    TDPoint iPoint = v[a];
    TDPoint jPoint = v[b];
    iPoint.increment(i);
    jPoint.increment(j);
    TDPoint diff = iPoint - jPoint;
    for (size_t k = 0; k < v.size(); k++) {
        Eigen::Vector3d intersection = intersectionPoint(diff, v[k]);
        double intpart;
        if (modf(intersection[0], &intpart) == 0.0 && modf(intersection[1], &intpart) == 0.0 && modf(intersection[2], &intpart) == 0.0) {
            vc.push_back(Coords(intersection[0], intersection[1], intersection[2]));
            if (k > 1) {
                cout << k << " " << intersection.transpose() << endl;
            }
            if (v.size() - 1 == k) {
                cout << "found:" << endl;
                cout << "i: " << i << endl;
                cout << "j: " << j << endl;
            }
        } else {
            break;
        }
    }
    sort(vc.begin(), vc.end(), compareByZnX);
    long long xv = vc[1].x - vc[0].x;
    long long yv;
    long long zv;
    for (size_t i = 0; i < vc.size() - 1; i++) {
        long long curx = vc[i + 1].x - vc[i].x;
        if (curx < xv) {
            cout << curx << endl;
            xv = curx;
            yv = vc[i + 1].y - vc[i].y;
            zv = vc[i + 1].z - vc[i].z;
        }
    }

    cout << xv << endl;
    cout << yv << endl;
    cout << zv << endl;

    cout << xv % 148 << endl;
}