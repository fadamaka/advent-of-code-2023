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

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<int> cardNumbs;
    map<int, int> winnerMap;

    for (int i = 0; i < lines.size(); i++) {
        cardNumbs.push_back(i);

        vector<string> card = splitByChar(splitByChar(lines[cardNumbs[i]], ':')[1], '|');
        set<string> winningNumbers = extractNums(card[0]);
        set<string> myNumbers = extractNums(card[1]);

        set<string> intersect;

        set_intersection(winningNumbers.begin(), winningNumbers.end(), myNumbers.begin(), myNumbers.end(), inserter(intersect, intersect.begin()));

        winnerMap.insert(pair<int, int>(i, intersect.size()));
    }

    int i = 0;

    while (i < cardNumbs.size()) {
        for (int j = cardNumbs[i] + 1; j <= cardNumbs[i] + winnerMap.find(cardNumbs[i])->second; j++) {
            cardNumbs.push_back(j);
        }
        i++;
    }
    cout << "result: " << cardNumbs.size();
}

set<string> extractNums(string str) {
    set<string> nums;
    for (int i = 1; i < str.length(); i += 3) {
        nums.insert(str.substr(i, 2));
    }
    return nums;
}