#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    for (auto &&i : lines) {
        vector<string> split = splitByChar(i, ':');
        vector<string> edges = splitByChar(split[1], ' ');
        edges.erase(edges.begin());
        cout << split[0] << ":";
        for (auto &&j : edges) {
            cout << " " << j;
        }
        cout << endl;
    }
}