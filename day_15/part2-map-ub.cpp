#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
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

namespace std {
template <>
struct hash<string> {
    size_t operator()(const string& x) const {
        return std::hash<int>{}(hasher(x));
    }
};
}  // namespace std

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> input = splitByChar(lines[0], ',');
    unordered_map<string, int> uMap;

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
        for (unordered_map<string, int>::local_iterator it = uMap.begin(i); it != uMap.end(i); ++it) {
            result += (hasher(it->first) + 1) * bSize-- * it->second;
        }
    }

    cout << result;
}