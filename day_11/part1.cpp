#include <..\utils\aoc.h>

#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<pair<int, int>> galaxies;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '#')
                galaxies.push_back(pair<int, int>(i, j));
        }
    }
    set<int> vX;
    set<int> vY;
    vector<pair<int, int>> expandedGalaxies;
    for (pair<int, int> p : galaxies) {
        vY.insert(p.first);
        vX.insert(p.second);
    }
    int yOffset = 0;
    int xOffset = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (vY.find(i) == vY.end()) {
            yOffset++;
        }
        xOffset = 0;
        for (int j = 0; j < lines[i].size(); j++) {
            if (vX.find(j) == vX.end()) {
                // cout << "expanded x: " << j << endl;
                xOffset++;
            }
            if (lines[i][j] == '#')
                expandedGalaxies.push_back(pair<int, int>(i + yOffset, j + xOffset));
        }
    }
    int result = 0;
    int count = 0;
    // int count2 = 0;
    // for (pair<int, int> p : expandedGalaxies) {
    //     cout << ++count2 << "y: " << p.first << " x: " << p.second << endl;
    // }
    for (int i = 0; i < expandedGalaxies.size(); i++) {
        pair<int, int> p = expandedGalaxies.at(i);
        for (int j = i + 1; j < expandedGalaxies.size(); j++) {
            pair<int, int> p2 = expandedGalaxies.at(j);
            result += (abs(p2.first - p.first) + abs(p2.second - p.second));
            count++;
            // cout << "distance between " << i + 1 << " and " << j + 1 << " is " << abs(p2.first - p.first) + abs(p2.second - p.second) << endl;
        }
    }
    cout << result;
}
