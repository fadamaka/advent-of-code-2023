#include <..\utils\aoc.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> extractNums(string);
int countReq(vector<int> inputVector);
vector<int> indexToVector(int index);

map<int, int> resultMap;
map<int, int> winnerMap;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<int> cardNumbs;

    for (int i = 0; i < lines.size(); i++) {
        cardNumbs.push_back(i);

        vector<string> card = splitByChar(splitByChar(lines[cardNumbs[i]], ':')[1], '|');
        set<string> winningNumbers = extractNums(card[0]);
        set<string> myNumbers = extractNums(card[1]);

        set<string> intersect;

        set_intersection(winningNumbers.begin(), winningNumbers.end(), myNumbers.begin(), myNumbers.end(), inserter(intersect, intersect.begin()));

        winnerMap.insert(pair<int, int>(i, intersect.size()));
    }

    cout << "result: " << countReq(cardNumbs) - 1;
}

set<string> extractNums(string str) {
    set<string> nums;
    for (int i = 1; i < str.length(); i += 3) {
        nums.insert(str.substr(i, 2));
    }
    return nums;
}

int countReq(vector<int> inputVector) {
    if (inputVector.empty()) {
        return 1;
    }
    int count = 0;
    for (int i : inputVector) {
        int result;
        if (!resultMap.count(i)) {
            result = countReq(indexToVector(i));
            resultMap.insert(pair<int, int>(i, result));
        } else {
            result = resultMap.find(i)->second;
        }
        count += result;
    }
    return count + 1;
}

vector<int> indexToVector(int index) {
    vector<int> result;
    for (int j = index + 1; j <= index + winnerMap.find(index)->second; j++) {
        result.push_back(j);
    }
    if (result.empty()) {
    }
    return result;
}