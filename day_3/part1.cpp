#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    for (string line : lines) {
        cout << line << endl;
    }
}