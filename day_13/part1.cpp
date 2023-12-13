#include <..\utils\aoc.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> transpose(vector<string> data) {
    vector<string> result;
    for (int i = 0; i < data[0].size(); i++) {
        string str;
        for (int j = 0; j < data.size(); j++) {
            str += data[j][i];
        }
        result.push_back(str);
    }
    return result;
}

int findMirror(vector<string> field, map<string, set<int>> m) {
    set<int> prevCandidates;
    for (int i = 0; i < field.size(); i++) {
        int candidate = i + 1;
        set<int> candidates;
        set<int> dupes = m.find(field[i])->second;
        if (dupes.size() >= 2) {
            set<int> newCands;
            candidates.insert(dupes.begin(), dupes.end());
            candidates.erase(candidate);
            if (prevCandidates.size() > 0) {
                int matches = 0;
                for (int x : prevCandidates) {
                    if (candidates.find(x - 1) != candidates.end()) {
                        matches++;
                        newCands.insert(x - 1);
                    }
                }
                if (matches == 0) {
                    break;
                } else {
                    prevCandidates = newCands;
                }
            } else {
                prevCandidates = candidates;
            }
            if (prevCandidates.find(i + 2) != prevCandidates.end()) {
                return i + 1;
            }
        } else {
            break;
        }
    }

    prevCandidates.clear();
    for (int i = field.size() - 1; i >= 0; i--) {
        int candidate = i + 1;
        set<int> candidates;
        set<int> dupes = m.find(field[i])->second;
        if (dupes.size() >= 2) {
            set<int> newCands;
            candidates.insert(dupes.begin(), dupes.end());
            candidates.erase(candidate);
            if (prevCandidates.size() > 0) {
                int matches = 0;
                for (int x : prevCandidates) {
                    if (candidates.find(x + 1) != candidates.end()) {
                        matches++;
                        newCands.insert(x + 1);
                    }
                }
                if (matches == 0) {
                    break;
                } else {
                    prevCandidates = newCands;
                }
            } else {
                prevCandidates = candidates;
            }
            if (prevCandidates.find(i) != prevCandidates.end()) {
                return i;
            }
        } else {
            break;
        }
    }
    return 0;
}
map<string, set<int>> generateMap(vector<string> field) {
    map<string, set<int>> m;
    for (int i = 0; i < field.size(); i++) {
        if (m.count(field[i]) == 0) {
            m.insert(pair<string, set<int>>(field[i], {i + 1}));
        } else {
            m.find(field[i])->second.insert(i + 1);
        }
    }
    return m;
}
vector<map<string, set<int>>> generateMapVector(vector<vector<string>> parsedInput) {
    vector<map<string, set<int>>> maps;
    for (int j = 0; j < parsedInput.size(); j++) {
        vector<string> field = parsedInput[j];
        maps.push_back(generateMap(field));
    }
    return maps;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<vector<string>> parsedInput;

    int fieldCount = 0;
    parsedInput.push_back(vector<string>());
    for (string str : lines) {
        if (str.size() == 0) {
            parsedInput.push_back(vector<string>());
            ++fieldCount;
        } else {
            parsedInput[fieldCount].push_back(str);
        }
    }

    // vertical segment
    vector<map<string, set<int>>> vertMaps = generateMapVector(parsedInput);

    int result = 0;

    // horizontal segment
    vector<vector<string>> pivotedInput;
    transform(parsedInput.begin(), parsedInput.end(), back_inserter(pivotedInput), [](const vector<string>& v) { return transpose(v); });

    vector<map<string, set<int>>> horMaps = generateMapVector(pivotedInput);

    for (size_t i = 0; i < vertMaps.size(); i++) {
        map<string, set<int>> m = vertMaps[i];
        vector<string> strV = parsedInput[i];
        int mirrorpoz = findMirror(strV, m);
        // cout << i + 1 << ": horizontal mirror poz: " << mirrorpoz << endl;

        map<string, set<int>> m2 = horMaps[i];
        vector<string> strV2 = pivotedInput[i];
        int mirrorpoz2 = findMirror(strV2, m2);

        // cout << i + 1 << ": vertical mirror poz: " << mirrorpoz2 << endl;
        if (mirrorpoz2 == 0 && mirrorpoz == 0) {
            cout << "vmi" << endl;
        }
        if (mirrorpoz2 != 0 && mirrorpoz != 0) {
            cout << "vmi" << endl;
        }
        result += mirrorpoz2;
        result += mirrorpoz * 100;
    }
    cout << "result: " << result << endl;
}