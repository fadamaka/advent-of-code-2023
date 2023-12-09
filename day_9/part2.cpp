#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int getExtra(vector<int> v);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<vector<int>> input;

    transform(lines.begin(), lines.end(), back_inserter(input), [](const string& str) {
        vector<int> v;
        vector<string> sv;
        sv = splitByChar(str, ' ');
        transform(sv.begin(), sv.end(), back_inserter(v), [](const string& str) { return stoi(str); });
        return v;
    });
    long long result = 0;
    for (vector<int> v : input) {
        result += getExtra(v);
    }
    cout << result << endl;
}

int getExtra(vector<int> v) {
    vector<int> proc;
    for (int i = 0; i < v.size() - 1; i++) {
        proc.push_back(v[i + 1] - v[i]);
    }
    set<int> procSet(proc.begin(), proc.end());
    if (procSet.size() == 1) {
        return *v.begin() - *procSet.begin();
    } else {
        return *v.begin() - getExtra(proc);
    }
}