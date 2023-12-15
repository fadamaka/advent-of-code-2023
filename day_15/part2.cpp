#include <..\utils\aoc.h>

#include <iostream>
#include <set>
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
    string testInput = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> input = splitByChar(lines[0], ',');
    vector<pair<string, int>> array[256];
    for (string str : input) {
        if (str.find('=') != string::npos) {
            vector<string> split = splitByChar(str, '=');
            if (array[hasher(split[0])].size() > 0) {
                set<string> keySet;
                for (pair<string, int> p : array[hasher(split[0])]) {
                    keySet.insert(p.first);
                }
                if (keySet.find(split[0]) != keySet.end()) {
                    for (pair<string, int> &p : array[hasher(split[0])]) {
                        if (p.first == split[0]) {
                            p.second = stoi(split[1]);
                            break;
                        }
                    }
                } else {
                    array[hasher(split[0])].push_back(pair<string, int>(split[0], stoi(split[1])));
                }

            } else {
                array[hasher(split[0])].push_back(pair<string, int>(split[0], stoi(split[1])));
            }

        } else {
            vector<string> split = splitByChar(str, '-');

            if (array[hasher(split[0])].size() > 0) {
                set<string> keySet;
                for (pair<string, int> p : array[hasher(split[0])]) {
                    keySet.insert(p.first);
                }

                if (keySet.find(split[0]) != keySet.end()) {
                    for (vector<pair<string, int>>::iterator it = array[hasher(split[0])].begin();
                         it != array[hasher(split[0])].end();
                         it++) {
                        if (it->first == split[0]) {
                            array[hasher(split[0])].erase(it);
                            break;
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < 256; i++) {
        if (array[i].size() > 0) {
            int count = 1;
            for (pair<string, int> p : array[i]) {
                result += (i + 1) * count * p.second;
                count++;
            }
        }
    }
    cout << result;
}