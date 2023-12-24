#include <..\utils\aoc.h>
#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define mk_pair pair<double, double>
// display the x and y coordinates
void display(mk_pair par) {
    cout << "(" << par.first << ", " << par.second << ")" << endl;
}
mk_pair intersection(mk_pair A, mk_pair B, mk_pair C, mk_pair D) {
    // Line AB represented as a1x + b1y = c1
    double a = B.second - A.second;
    double b = A.first - B.first;
    double c = a * (A.first) + b * (A.second);
    // Line CD represented as a2x + b2y = c2
    double a1 = D.second - C.second;
    double b1 = C.first - D.first;
    double c1 = a1 * (C.first) + b1 * (C.second);
    double det = a * b1 - a1 * b;
    if (det == 0) {
        return make_pair(FLT_MAX, FLT_MAX);
    } else {
        double x = (b1 * c - b * c1) / det;
        double y = (a * c1 - a1 * c) / det;
        return make_pair(x, y);
    }
}
int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    mk_pair q = make_pair(20, 25);
    mk_pair r = make_pair(18, 23);
    mk_pair s = make_pair(18, 19);
    mk_pair t = make_pair(17, 18);
    mk_pair inter = intersection(q, r, s, t);
    if (inter.first == FLT_MAX && inter.second == FLT_MAX) {
        cout << "The given lines AB and CD are parallel.\n";
    } else {
        cout << "The intersection of the given lines AB and CD is: ";
        display(inter);
    }
    return 0;
}