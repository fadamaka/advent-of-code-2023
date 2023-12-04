#include <..\utils\aoc.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> extractNums(string);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<int> cardNumbs;

    for (int i = 0; i < lines.size(); i++) {
        cardNumbs.push_back(i);
    }

    // cout << cardNumbs.size() << endl;

    int sum = 0;

    int i = 0;

    while (i < cardNumbs.size()) {
        string line = lines[cardNumbs[i]];
        // if (i % 1000000 == 0)
        //     cout << "i: " << i << endl;
        vector<string> card = splitByChar(splitByChar(line, ':')[1], '|');
        set<string> winningNumbers = extractNums(card[0]);
        set<string> myNumbers = extractNums(card[1]);

        set<string> intersect;

        set_intersection(winningNumbers.begin(), winningNumbers.end(), myNumbers.begin(), myNumbers.end(), inserter(intersect, intersect.begin()));

        if (intersect.size() > 0) {
            sum += pow(2, (intersect.size() - 1));
        }

        for (int j = cardNumbs[i] + 1; j <= cardNumbs[i] + intersect.size(); j++) {
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