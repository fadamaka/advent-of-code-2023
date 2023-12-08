#include <..\utils\aoc.h>

#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    map<string, pair<string, string>> keyMap;
    string directions = lines[0];
    vector<string> startingPoints;

    for (int i = 2; i < lines.size(); i++) {
        vector<string> key = splitByChar(lines[i], '=');
        vector<string> dests = splitByChar(key[1], ',');
        keyMap.insert(pair<string, pair<string, string>>(key[0].substr(0, 3), pair<string, string>(dests[0].substr(2, 3), dests[1].substr(1, 3))));
        if (key[0].substr(0, 3)[2] == 'A') {
            startingPoints.push_back(key[0].substr(0, 3));
        }
    }
    unsigned long long result = stoll("1");
    for (string str : startingPoints) {
        string currentPoz = str;
        int count = 0;
        int directionPoz = 0;
        int exitCount = 0;
        int firstExit = 0;
        int secondExit = 0;
        while (exitCount < 2) {
            count++;
            if (directions[directionPoz] == 'L') {
                currentPoz = keyMap.find(currentPoz)->second.first;
            } else {
                currentPoz = keyMap.find(currentPoz)->second.second;
            }

            if (++directionPoz == directions.size()) {
                directionPoz = 0;
            }
            if (currentPoz[2] == 'Z') {
                if (exitCount == 0) {
                    firstExit = count;
                } else {
                    secondExit = count;
                }
                exitCount++;
                cout << count << " ";
            }
        }
        result = lcm(result, firstExit);
    }

    cout << result;
}