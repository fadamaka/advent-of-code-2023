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
int findMirror(vector<string> field, map<string, set<int>> m, int notThis) {
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
            if (prevCandidates.find(i + 2) != prevCandidates.end() && notThis != i + 1) {
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
            if (prevCandidates.find(i) != prevCandidates.end() && notThis != i) {
                return i;
            }
        } else {
            break;
        }
    }
    return 0;
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

int calculateField(vector<string> field) {
    map<string, set<int>> m = generateMap(field);
    int ogNorm = findMirror(field, m) * 100;
    vector<string> pField = transpose(field);
    m = generateMap(pField);
    int ogPv = findMirror(pField, m);

    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].size(); j++) {
            vector<string> v = field;
            char ch = field[i][j];
            if (ch == '.') {
                v[i][j] = '#';
            } else {
                v[i][j] = '.';
            }
            map<string, set<int>> newMap = generateMap(v);
            int newNorm = findMirror(v, newMap, ogNorm / 100) * 100;
            int newPv = 0;
            if (newNorm == ogNorm || newNorm == 0) {
                v = transpose(v);
                newMap = generateMap(v);
                newPv = findMirror(v, newMap, ogPv);
                if (newPv == ogPv || newPv == 0) {
                    continue;
                } else {
                    return newPv;
                }
            } else {
                return newNorm;
            }
        }
    }
    cout << "error" << endl;
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
    int result = 0;
    for (int i = 0; i < parsedInput.size(); i++) {
        vector<string> field = parsedInput[i];
        int subresult = calculateField(field);
        if (subresult == 0) {
            cout << i << endl;
        }
        result += subresult;
    }

    cout << "result: " << result << endl;
}