#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double polygonArea(vector<double> X, vector<double> Y, int sum) {
    // Initialize area
    double area = 0.0;
    int n = X.size();

    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i;  // j is previous vertex to i
    }

    // Return absolute value
    return abs((area - sum) / 2.0);
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<vector<string>> parsed;
    transform(lines.begin(), lines.end(), back_inserter(parsed), [](const string& str) { return splitByChar(str, ' '); });
    int y = 0;
    int x = 0;
    int sum = 0;
    vector<pair<int, int>> coords;
    vector<double> yV;
    vector<double> xV;
    for (auto&& i : parsed) {
        sum += stoi(i[1]);
        if (i[0] == "R") {
            x += stoi(i[1]);
        }
        if (i[0] == "L") {
            x -= stoi(i[1]);
        }
        if (i[0] == "U") {
            y -= stoi(i[1]);
        }
        if (i[0] == "D") {
            y += stoi(i[1]);
        }
        xV.push_back(x);
        yV.push_back(y);
        coords.push_back(pair<int, int>(y, x));
    }
    // cout << sum << endl;
    cout << polygonArea(yV, xV, sum) + sum + 1 << endl;
}