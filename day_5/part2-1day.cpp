#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> stringNums;
vector<vector<vector<long long>>> sepAlm;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    stringNums = splitByChar(lines.at(0).substr(7, lines.at(0).size() - 7), ' ');

    int vecFirst = 0;

    for (int i = 2; i < lines.size(); i++) {
        string line = lines.at(i);
        if (line.size() == 0 || i == lines.size() - 1) {
            vector<string>::const_iterator first = lines.begin() + vecFirst;
            vector<string>::const_iterator last = lines.begin() + i;
            vector<string> newVec(first, last);
            vector<vector<long long>> numNums;
            for (string line : newVec) {
                vector<string> strNums = splitByChar(line, ' ');
                vector<long long> nums;
                transform(strNums.begin(), strNums.end(), back_inserter(nums), [](const string &str) { return stoll(str); });
                numNums.push_back(nums);
            }

            sepAlm.push_back(numNums);
        } else {
            if (!isInt(line.at(0))) {
                vecFirst = i + 1;
            }
        }
    }

    long long lowestLoc = LLONG_MAX;
    for (int i = 0; i < stringNums.size(); i += 2) {
        long long source = stoll(stringNums[i]);
        for (long long j = stoll(stringNums[i]); j < (stoll(stringNums[i]) + stoll(stringNums[i + 1])); j++) {
            if ((j - stoll(stringNums[i])) % stoll("1000000") == 0) {
                cout << j - stoll(stringNums[i]) << endl;
                if ((j - stoll(stringNums[i])) > 0) {
                    return 0;
                }
            }
            source = j;
            long long dest = j;
            for (vector<vector<long long>> section : sepAlm) {
                for (int i = 0; i < section.size(); i++) {
                    vector<long long> nums = section.at(i);

                    long long elemSourceNum = source;
                    long long destNum = nums.at(0);
                    long long sourceNum = nums.at(1);
                    long long range = nums.at(2);
                    if (elemSourceNum >= sourceNum && elemSourceNum <= sourceNum + range) {
                        dest = elemSourceNum - sourceNum + destNum;
                        break;
                    }
                }
                source = dest;
            }

            if (source < lowestLoc) {
                lowestLoc = source;
            }
        }
        cout << i << endl;
    }
    cout << lowestLoc;
}