#include <..\utils\aoc.h>

#include <algorithm>
#include <future>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

using namespace std;

long long workFunc(long long startIndex, long long range);

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
                transform(strNums.begin(), strNums.end(), back_inserter(nums), [](const string& str) { return stoll(str); });
                numNums.push_back(nums);
            }

            sepAlm.push_back(numNums);
        } else {
            if (!isInt(line.at(0))) {
                vecFirst = i + 1;
            }
        }
    }
    vector<future<long long>> futureLongs;
    long long lowestLoc = LLONG_MAX;
    int thread = 0;
    for (int i = 0; i < stringNums.size(); i += 2) {
        for (long long j = stoll(stringNums[i]); j < (stoll(stringNums[i]) + stoll(stringNums[i + 1])); j += stoll("50000000")) {
            long long range = stoll("50000000");
            if ((range + j) > (stoll(stringNums[i]) + stoll(stringNums[i + 1]))) {
                range = (stoll(stringNums[i]) + stoll(stringNums[i + 1])) - j;
            }
            futureLongs.push_back(async(&workFunc, j, range));
            cout << "thread " << ++thread << " started" << endl;
        }
    }
    for (int i = 0; i < futureLongs.size(); i++) {
        long long currentCalc = futureLongs[i].get();
        if (currentCalc < lowestLoc) {
            lowestLoc = currentCalc;
        }
    }
    cout << lowestLoc;
}

long long workFunc(long long startIndex, long long range) {
    long long lowestLoc = LLONG_MAX;
    long long source = startIndex;
    for (long long j = startIndex; j < (startIndex + range); j++) {
        if ((j - startIndex) % stoll("1000000") == 0 && (j - startIndex) > 0) {
            cout << j - startIndex << endl;
            if ((j - startIndex) > 0) {
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
    return lowestLoc;
}