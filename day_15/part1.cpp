#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int hasher(string str) {
    int result = 0;
    for (char ch : str) {
        result += int(ch);
        result *= 17;
        result %= 256;
    }
    return result;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> input = splitByChar(lines[0], ',');
    int result = 0;
    for (string str : input) {
        result += hasher(str);
    }
    cout << result;
}