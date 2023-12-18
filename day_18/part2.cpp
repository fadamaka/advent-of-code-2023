#include <..\utils\aoc.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long polygonArea(vector<double> X, vector<double> Y, long sum) {
    // Initialize area
    long double area = 0.0;
    long n = X.size();

    // Calculate value of shoelace formula
    long j = n - 1;
    for (int i = 0; i < n; i++) {
        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i;  // j is previous vertex to i
    }

    // Return absolute value
    return floor(abs((area - sum) / 2.0));
}

long hexadecimalToDecimal(string hexVal) {
    long len = hexVal.size();

    // Initializing base value to 1,
    // i.e 16^0
    long base = 1;

    long dec_val = 0;

    // Extracting characters as digits
    // from last character
    for (int i = len - 1; i >= 0; i--) {
        // If character lies in '0'-'9',
        // converting it to integral 0-9
        // by subtracting 48 from ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // If character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f') {
            dec_val += (int(hexVal[i]) - 87) * base;

            // Incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<vector<string>> parsed;
    transform(lines.begin(), lines.end(), back_inserter(parsed), [](const string& str) { return splitByChar(str, ' '); });
    long y = 0;
    long x = 0;
    long sum = 0;
    vector<pair<int, int>> coords;
    vector<double> yV;
    vector<double> xV;
    for (auto&& i : parsed) {
        sum += hexadecimalToDecimal(i[2].substr(2, 5));
        if (i[2][7] == '0') {
            // cout << "R " << hexadecimalToDecimal(i[2].substr(2, 5)) << endl;
            x += hexadecimalToDecimal(i[2].substr(2, 5));
        }
        if (i[2][7] == '2') {
            // cout << "L " << hexadecimalToDecimal(i[2].substr(2, 5)) << endl;
            x -= hexadecimalToDecimal(i[2].substr(2, 5));
        }
        if (i[2][7] == '3') {
            // cout << "U " << hexadecimalToDecimal(i[2].substr(2, 5)) << endl;
            y -= hexadecimalToDecimal(i[2].substr(2, 5));
        }
        if (i[2][7] == '1') {
            // cout << "D " << hexadecimalToDecimal(i[2].substr(2, 5)) << endl;
            y += hexadecimalToDecimal(i[2].substr(2, 5));
        }
        xV.push_back(x);
        yV.push_back(y);
        coords.push_back(pair<int, int>(y, x));
    }
    // cout << sum << endl;
    cout << polygonArea(yV, xV, sum) + sum + 1 << endl;
}