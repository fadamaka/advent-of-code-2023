#include <..\utils\aoc.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    map<string, pair<string, string>> keyMap;
    string directions = lines[0];

    for (int i = 2; i < lines.size(); i++) {
        vector<string> key = splitByChar(lines[i], '=');
        vector<string> dests = splitByChar(key[1], ',');
        keyMap.insert(pair<string, pair<string, string>>(key[0].substr(0, 3), pair<string, string>(dests[0].substr(2, 3), dests[1].substr(1, 3))));
    }
    string currentPoz = "AAA";
    int count = 0;
    int directionPoz = 0;
    while (currentPoz != "ZZZ") {
        count++;
        if (directions[directionPoz] == 'L') {
            currentPoz = keyMap.find(currentPoz)->second.first;
        } else {
            currentPoz = keyMap.find(currentPoz)->second.second;
        }

        if (++directionPoz == directions.size()) {
            directionPoz = 0;
        }
    }
    cout << count;
}