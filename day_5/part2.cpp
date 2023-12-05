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

vector<pair<long long, long long>> translateRange(vector<pair<long long, long long>> ranges, int level);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    stringNums = splitByChar(lines.at(0).substr(7, lines.at(0).size() - 7), ' ');
    vector<pair<long long, long long>> ranges;

    for (int i = 0; i < stringNums.size(); i += 2) {
        ranges.push_back(pair<long long, long long>(stoll(stringNums[i]), stoll(stringNums[i + 1])));
    }

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

    long long lowestLoc = LLONG_MAX;
    for (pair<long long, long long> locs : translateRange(ranges, 0)) {
        if (locs.first < lowestLoc) {
            lowestLoc = locs.first;
        }
    }
    cout << lowestLoc;
}

vector<pair<long long, long long>> translateRange(vector<pair<long long, long long>> ranges, int level) {
    vector<pair<long long, long long>> newRanges;

    vector<vector<long long>> rules = sepAlm.at(level);
    vector<pair<long long, long long>> rangesCopy = ranges;
    for (int i = 0; i < rangesCopy.size(); i++) {
        pair<long long, long long> localRange = rangesCopy[i];
        bool deletePair = false;
        for (vector<long long> nums : rules) {
            long long myNum = localRange.first;
            long long myRange = localRange.second;
            long long toNum = nums.at(0);
            long long fromNum = nums.at(1);
            long long ruleRange = nums.at(2);

            if (myNum >= fromNum && myNum < (fromNum + ruleRange) && (myNum + myRange) <= (fromNum + ruleRange)) {
                newRanges.push_back(pair<long long, long long>(myNum - fromNum + toNum, myRange));
                deletePair = true;
                break;
            }
            if (myNum < fromNum && (myNum + myRange) >= fromNum & (myNum + myRange) <= (fromNum + ruleRange)) {
                newRanges.push_back(pair<long long, long long>(toNum, myRange - (fromNum - myNum)));
                myRange = fromNum - myNum;
                localRange.second = myRange;
                continue;
            }
            if ((myNum + myRange) > (fromNum + ruleRange) && myNum >= fromNum && myNum < (fromNum + ruleRange)) {
                newRanges.push_back(pair<long long, long long>(myNum - fromNum + toNum, fromNum + ruleRange - myNum));
                myRange += myNum;
                myNum = fromNum + ruleRange;
                myRange -= myNum;
                localRange.first = myNum;
                localRange.second = myRange;
                continue;
            }
            if ((myNum + myRange) > (fromNum + ruleRange) && myNum < fromNum) {
                newRanges.push_back(pair<long long, long long>(toNum, ruleRange));
                rangesCopy.push_back(pair<long long, long long>(fromNum + ruleRange, myNum + myRange - fromNum - ruleRange));
                myRange = fromNum - myNum;
                localRange.second = myRange;
                continue;
            }
        }
        if (!deletePair) {
            newRanges.push_back(localRange);
        }
    }
    if (level >= 6) {
        return newRanges;
    }

    return translateRange(newRanges, level + 1);
}
