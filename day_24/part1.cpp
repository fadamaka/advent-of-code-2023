#include <..\utils\aoc.h>
#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
#define mk_pair pair<long double, long double>
// display the x and y coordinates
void display(mk_pair par) {
    cout << "(" << par.first << ", " << par.second << ")" << endl;
}
mk_pair intersection(mk_pair A, mk_pair B, mk_pair C, mk_pair D) {
    // Line AB represented as a1x + b1y = c1
    long double a = B.second - A.second;
    long double b = A.first - B.first;
    long double c = a * (A.first) + b * (A.second);
    // Line CD represented as a2x + b2y = c2
    long double a1 = D.second - C.second;
    long double b1 = C.first - D.first;
    long double c1 = a1 * (C.first) + b1 * (C.second);
    long double det = a * b1 - a1 * b;
    if (det == 0) {
        return make_pair(LDBL_MAX, LDBL_MAX);
    } else {
        long double x = (b1 * c - b * c1) / det;
        long double y = (a * c1 - a1 * c) / det;

        if ((b < 0 && B.first > x) || (b1 < 0 && D.first > x) || (b > 0 && B.first < x) || (b1 > 0 && D.first < x) || (a > 0 && B.second > y) || (a1 > 0 && D.second > y) || (a < 0 && B.second < y) || (a1 < 0 && D.second < y)) {
            return make_pair(LDBL_MAX, LDBL_MAX);
        }

        return make_pair(x, y);
    }
}
int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<pair<pair<long double, long double>, pair<long double, long double>>> points;
    for (string str : lines) {
        vector<string> firstPlit = splitByChar(str, '@');
        vector<string> firstPoint = splitByChar(firstPlit[0], ',');
        long double ax = stold(firstPoint[0]);
        long double ay = stold(firstPoint[1].substr(1));
        vector<string> secondPoint = splitByChar(firstPlit[1], ',');
        long double bx = stold(firstPoint[0]) + stold(secondPoint[0].substr(1));
        long double by = stold(firstPoint[1].substr(1)) + stold(secondPoint[1].substr(1));
        points.push_back(pair<pair<long double, long double>, pair<long double, long double>>(
            pair<long double, long double>(ax, ay),
            pair<long double, long double>(bx, by)));
    }
    int counter = 0;
    for (int i = 0; i < points.size(); i++) {
        auto line = points[i];
        mk_pair q = make_pair(line.first.first, line.first.second);
        mk_pair r = make_pair(line.second.first, line.second.second);
        for (int j = i + 1; j < points.size(); j++) {
            auto secondLine = points[j];
            mk_pair s = make_pair(secondLine.first.first, secondLine.first.second);
            mk_pair t = make_pair(secondLine.second.first, secondLine.second.second);
            // display(q);
            // display(s);
            mk_pair inter = intersection(q, r, s, t);
            if (inter.first == LDBL_MAX && inter.second == LDBL_MAX) {
                // cout << "The given lines AB and CD are parallel.\n";
            } else {
                if (inter.first >= 200000000000000.0L && inter.second >= 200000000000000.0L && inter.first <= 400000000000000.0L && inter.second <= 400000000000000.0L) {
                    // display(q);
                    // display(s);
                    // cout << "The intersection of the given lines AB and CD is: ";
                    // display(inter);
                    counter++;
                }
            }
        }
    }
    cout << "result: " << counter << endl;
    return 0;
}