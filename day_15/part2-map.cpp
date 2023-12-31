#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Hash {
    size_t operator()(const string& str) const {
        size_t hash{};
        for (const auto c : str) {
            hash += size_t(c);
            hash *= 17;
            hash %= 256;
        }
        return hash;
    }
};

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> input = splitByChar(lines[0], ',');

    unordered_map<string, int, Hash> uMap;

    for (string str : input) {
        if (str.find('=') != string::npos) {
            vector<string> split = splitByChar(str, '=');
            uMap[split[0]] = stoi(split[1]);
        } else {
            vector<string> split = splitByChar(str, '-');
            uMap.erase(split[0]);
        }
    }

    int result = 0;

    for (int i = 0; i < uMap.bucket_count(); i++) {
        int bSize = uMap.bucket_size(i);
        for (unordered_map<string, int, Hash>::local_iterator it = uMap.begin(i); it != uMap.end(i); ++it) {
            result += (i + 1) * bSize-- * it->second;
        }
    }

    cout << result;
}