#include <..\utils\aoc.h>

#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<pair<long long, long long>> galaxies;

    for (long long i = 0; i < lines.size(); i++) {
        for (long long j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '#')
                galaxies.push_back(pair<long long, long long>(i, j));
        }
    }
    set<long long> vX;
    set<long long> vY;
    vector<pair<long long, long long>> expandedGalaxies;
    for (pair<long long, long long> p : galaxies) {
        vY.insert(p.first);
        vX.insert(p.second);
    }
    long long yOffset = 0;
    long long xOffset = 0;
    for (long long i = 0; i < lines.size(); i++) {
        if (vY.find(i) == vY.end()) {
            yOffset += stoll("999999");
        }
        xOffset = 0;
        for (long long j = 0; j < lines[i].size(); j++) {
            if (vX.find(j) == vX.end()) {
                // cout << "expanded x: " << j << endl;
                xOffset += stoll("999999");
            }
            if (lines[i][j] == '#')
                expandedGalaxies.push_back(pair<long long, long long>(i + yOffset, j + xOffset));
        }
    }
    long long result = 0;
    long long count = 0;
    // long long count2 = 0;
    // for (pair<long long, long long> p : expandedGalaxies) {
    //     cout << ++count2 << "y: " << p.first << " x: " << p.second << endl;
    // }
    for (long long i = 0; i < expandedGalaxies.size(); i++) {
        pair<long long, long long> p = expandedGalaxies.at(i);
        for (long long j = i + 1; j < expandedGalaxies.size(); j++) {
            pair<long long, long long> p2 = expandedGalaxies.at(j);
            result += (abs(p2.first - p.first) + abs(p2.second - p.second));
            count++;
            // cout << "distance between " << i + 1 << " and " << j + 1 << " is " << abs(p2.first - p.first) + abs(p2.second - p.second) << endl;
        }
    }
    cout << result;
}
