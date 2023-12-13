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
    // this assumes that all inner vectors have the same size and
    // allocates space for the complete result in advance
    vector<string> result;
    for (int i = 0; i < data[0].size(); i++) {
        string str;
        for (int j = 0; j < data.size(); j++) {
            str += data[j][i];
        }
        // cout << "pos: " << str << endl;
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
            // for (int x : dupes) {
            //     cout << " " << x;
            // }
            // cout << endl;
            // int f = *(dupes.begin());
            // int s = *next(dupes.begin(), 1);

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
            // for (int x : dupes) {
            //     cout << " " << x;
            // }
            // cout << endl;
            // int f = *(dupes.begin());
            // int s = *next(dupes.begin(), 1);

            if (prevCandidates.find(i) != prevCandidates.end()) {
                return i;
            }
        } else {
            break;
        }
    }
    return 0;
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
    vector<map<string, set<int>>> vertMaps;

    for (int j = 0; j < parsedInput.size(); j++) {
        vector<string> field = parsedInput[j];
        vertMaps.push_back(map<string, set<int>>());
        for (int i = 0; i < field.size(); i++) {
            // cout << field[i] << endl;
            if (vertMaps[j].count(field[i]) == 0) {
                vertMaps[j].insert(pair<string, set<int>>(field[i], {i + 1}));
            } else {
                vertMaps[j].find(field[i])->second.insert(i + 1);
            }
        }
        // cout << endl;
    }

    // for (map<string, set<int>> m : vertMaps) {
    //     cout << endl;
    //     for (pair<string, set<int>> p : m) {
    //         cout << p.first;
    //         for (int i : p.second) {
    //             cout << " " << i;
    //         }

    //         cout << endl;
    //     }
    // }
    int result = 0;

    // horizontal segment
    vector<vector<string>> pivotedInput;
    transform(parsedInput.begin(), parsedInput.end(), back_inserter(pivotedInput), [](const vector<string>& v) { return transpose(v); });

    vector<map<string, set<int>>> horMaps;

    for (int j = 0; j < pivotedInput.size(); j++) {
        vector<string> field = pivotedInput[j];
        horMaps.push_back(map<string, set<int>>());
        for (int i = 0; i < field.size(); i++) {
            // cout << field[i] << endl;
            if (horMaps[j].count(field[i]) == 0) {
                horMaps[j].insert(pair<string, set<int>>(field[i], {i + 1}));
            } else {
                horMaps[j].find(field[i])->second.insert(i + 1);
            }
        }
        // cout << endl;
    }

    // int debug = 57;

    // for (string str : parsedInput[debug]) {
    //     cout << str << endl;
    // }
    // cout << endl;
    // for (pair<string, set<int>> p : vertMaps[debug]) {
    //     cout << p.first;
    //     for (int i : p.second) {
    //         cout << " " << i;
    //     }

    //     cout << endl;
    // }

    // cout << findMirror(parsedInput[debug], vertMaps[debug]);

    // cout << endl;
    // for (string str : pivotedInput[debug]) {
    //     cout << str << endl;
    // }
    // cout << endl;
    // for (pair<string, set<int>> p : horMaps[debug]) {
    //     cout << p.first;
    //     for (int i : p.second) {
    //         cout << " " << i;
    //     }

    //     cout << endl;
    // }

    // cout << findMirror(pivotedInput[debug], horMaps[debug]);

    // return 0;

    for (size_t i = 0; i < vertMaps.size(); i++) {
        map<string, set<int>> m = vertMaps[i];
        vector<string> strV = parsedInput[i];
        int mirrorpoz = findMirror(strV, m);
        cout << i + 1 << ": horizontal mirror poz: " << mirrorpoz << endl;

        map<string, set<int>> m2 = horMaps[i];
        vector<string> strV2 = pivotedInput[i];
        int mirrorpoz2 = findMirror(strV2, m2);

        cout << i + 1 << ": vertical mirror poz: " << mirrorpoz2 << endl;
        if (mirrorpoz2 == 0 && mirrorpoz == 0) {
            cout << "vmi" << endl;
        }
        if (mirrorpoz2 != 0 && mirrorpoz != 0) {
            cout << "vmi" << endl;
        }
        result += mirrorpoz2;
        result += mirrorpoz * 100;
    }

    cout << "result: " << result;
}