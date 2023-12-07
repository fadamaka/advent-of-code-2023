#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

enum strength {
    high,
    twook,
    twop,
    threeok,
    full,
    fourok,
    fiveok
};

strength getType(string str);
short getNumbers(string subject, char ch);
string translateEnum(strength type);
string replaceChar(string str);

struct Hand {
    string str;
    int bid;
    strength type;
    string tieBreaker;

    Hand(string in) {
        vector<string> split = splitByChar(in, ' ');
        str = split[0];
        bid = stoi(split[1]);
        type = getType(split[0]);
        tieBreaker = replaceChar(split[0]);
    }

    bool operator<(const Hand& val) const {
        if (type != val.type) {
            return type < val.type;
        }
        return tieBreaker < val.tieBreaker;
    }
};

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<Hand> hands;

    transform(lines.begin(), lines.end(), back_inserter(hands), [](const string& str) { return Hand(str); });
    sort(hands.begin(), hands.end());
    // for (Hand hand : hands) {
    //     cout << hand.str << " bid: " << hand.bid << " type: " << translateEnum(hand.type) << " tiebreaker: " << hand.tieBreaker << endl;
    // }
    long long result = 0;
    for (int i = 0; i < hands.size(); i++) {
        result += (hands[i].bid * (i + 1));
    }
    cout << result;
}

strength getType(string str) {
    string newStr;
    short jCount = 0;
    if (str.find('J') != string::npos) {
        for (char ch : str) {
            if (ch == 'J') {
                jCount++;
            } else {
                newStr += ch;
            }
        }
        str = newStr;
    }
    if (jCount == 5) {
        return fiveok;
    }
    set<char> charSet(str.begin(), str.end());
    if (charSet.size() == 5) {
        return high;
    }
    if (charSet.size() == 1) {
        return fiveok;
    }
    if (charSet.size() == 4) {
        return twook;
    }
    set<short> matchSet;
    for (char ch : charSet) {
        matchSet.insert(getNumbers(str, ch));
    }
    if (jCount != 0) {
        reverse_iterator<set<short>::iterator> it = matchSet.rbegin();
        short highest = *it;
        matchSet.erase(highest);
        matchSet.insert(highest + jCount);
    }
    if (matchSet.find(3) != matchSet.end()) {
        if (charSet.size() == 2) {
            return full;
        } else {
            return threeok;
        }
    }
    if (matchSet.find(4) != matchSet.end()) {
        return fourok;
    }
    if (matchSet.find(2) != matchSet.end()) {
        return twop;
    }

    cout << "error" << endl;
    return high;
}

short getNumbers(string subject, char ch) {
    return count_if(subject.begin(), subject.end(), [&ch](char i) { return i == ch; });
}

string translateEnum(strength type) {
    switch (type) {
        case high:
            return "high card";
        case twook:
            return "one pair";
        case twop:
            return "two pairs";
        case threeok:
            return "three of a kind";
        case full:
            return "fullhouse";
        case fourok:
            return "four of a kind";
        case fiveok:
            return "five of a kind";
        default:
            return "error";
    }
}

string replaceChar(string str) {
    string newStr;
    for (char ch : str) {
        if (ch == 'T') {
            newStr += 'A';
            continue;
        }
        if (ch == 'J') {
            newStr += '1';
            continue;
        }
        if (ch == 'Q') {
            newStr += 'C';
            continue;
        }

        if (ch == 'K') {
            newStr += 'D';
            continue;
        }
        if (ch == 'A') {
            newStr += 'E';
            continue;
        }
        newStr += ch;
    }
    return newStr;
}