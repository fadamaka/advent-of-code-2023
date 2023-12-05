#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, long long> createSeed(long long seed);
void printMap(map<string, long long> myMap);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<map<string, long long>> seedMaps;
    for (string num : splitByChar(lines.at(0).substr(7, lines.at(0).size() - 7), ' ')) {
        seedMaps.push_back(createSeed(stoll(num)));
    }
    vector<vector<string>> sepAlm;

    int vecFirst = 0;

    for (int i = 2; i < lines.size(); i++) {
        string line = lines.at(i);
        if (line.size() == 0 || i == lines.size() - 1) {
            vector<string>::const_iterator first = lines.begin() + vecFirst;
            vector<string>::const_iterator last = lines.begin() + i;
            vector<string> newVec(first, last);
            sepAlm.push_back(newVec);
        } else {
            if (!isInt(line.at(0))) {
                vecFirst = i;
            }
        }
    }

    for (vector<string> section : sepAlm) {
        vector<string> firstLine = splitByChar(section.at(0).substr(0, section.at(0).size() - 5), '-');
        string source = firstLine.at(0);
        string dest = firstLine.at(2);
        // cout << source << " to " << dest << endl;
        for (int i = 1; i < section.size(); i++) {
            string line = section.at(i);
            vector<string> strNums = splitByChar(line, ' ');
            vector<long long> nums;
            transform(strNums.begin(), strNums.end(), back_inserter(nums), [](const string &str) { return stoll(str); });
            for (map<string, long long> &seedMap : seedMaps) {
                if (seedMap.count(dest) == 0) {
                    long long elemSourceNum = seedMap.find(source)->second;
                    long long destNum = nums.at(0);
                    long long sourceNum = nums.at(1);
                    long long range = nums.at(2);
                    if (elemSourceNum >= sourceNum && elemSourceNum <= sourceNum + range) {
                        seedMap.insert(pair<string, long long>(dest, elemSourceNum - sourceNum + destNum));
                    }
                }
            }
        }

        for (map<string, long long> &seedMap : seedMaps) {
            if (seedMap.count(dest) == 0) {
                seedMap.insert(pair<string, long long>(dest, seedMap.find(source)->second));
            }
        }
    }
    long long lowestLoc = LLONG_MAX;
    for (map<string, long long> eMap : seedMaps) {
        if (eMap.find("location")->second < lowestLoc) {
            lowestLoc = eMap.find("location")->second;
        }
    }
    cout << lowestLoc;
}

map<string, long long> createSeed(long long seed) {
    map<string, long long> result;
    result.insert(pair<string, long long>("seed", seed));
    return result;
}

void printMap(map<string, long long> myMap) {
    for (map<string, long long>::const_iterator it = myMap.begin();
         it != myMap.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}