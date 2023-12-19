#include <..\utils\aoc.h>

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Rule {
    bool onlyTarget;
    char prop;
    int value;
    char rule;
    string target;
    Rule(char propCh, int valueIn, char ruleIn, string wfName) {
        prop = propCh;
        value = valueIn;
        rule = ruleIn;
        target = wfName;
        onlyTarget = false;
    };
    Rule(string wfName) {
        target = wfName;
        onlyTarget = true;
    };
    Rule negateRule() {
        if (rule == '<') {
            return Rule(prop, value - 1, '>', "n");
        } else {
            return Rule(prop, value + 1, '<', "n");
        }
    }
};
struct Part {
    int x;
    int m;
    int a;
    int s;
    Part(string strX, string strM, string strA, string strS) {
        x = stoi(strX);
        m = stoi(strM);
        a = stoi(strA);
        s = stoi(strS);
    }
    int getValue(char in) {
        switch (in) {
            case 'x':
                return x;
                break;
            case 'm':
                return m;
                break;
            case 'a':
                return a;
                break;
            case 's':
                return s;
                break;

            default:
                break;
        }
        return 0;
    }
    bool invoke(char ch, int y, char comp) {
        int x = getValue(ch);
        return comp == '<' ? x < y : x > y;
    }
    int getSum() {
        return x + m + a + s;
    }
};
struct Workflow {
    vector<Rule> rulesV;
    Workflow() {
        rulesV = vector<Rule>();
    };
};

unordered_map<string, Workflow> wfMap;
vector<Workflow> possibleWfs;

void findWins(string name, vector<Rule> rV) {
    if (name == "A" && rV[rV.size() - 1].target == "A") {
        Workflow newWf;
        newWf.rulesV = rV;
        possibleWfs.push_back(newWf);
        return;
    }
    if (name == "R") {
        return;
    }
    Workflow wf = wfMap.find(name)->second;
    for (Rule r : wf.rulesV) {
        vector<Rule> newRv;
        for (Rule rr : rV) {
            newRv.push_back(rr);
        }
        newRv.push_back(r);
        findWins(r.target, newRv);

        rV.push_back(r.negateRule());
    }
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<Part> parts;
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 0) {
            break;
        }

        vector<string> fV = splitByChar(lines[i], '{');
        string wfName = fV[0];
        vector<string> rulesV = splitByChar(fV[1].substr(0, fV[1].size() - 1), ',');
        Workflow wf;
        for (string str : rulesV) {
            if (str.find(':') != string::npos) {
                vector<string> ruleV = splitByChar(str, ':');
                wf.rulesV.push_back(Rule(ruleV[0][0], stoi(ruleV[0].substr(2)), ruleV[0][1], ruleV[1]));
            } else {
                wf.rulesV.push_back(Rule(str));
            }
        }
        wfMap.insert(pair<string, Workflow>(wfName, wf));
    }

    findWins("in", vector<Rule>());
    long long part2 = 0;
    for (Workflow wf : possibleWfs) {
        long long xMax = 4001;
        long long xMin = 0;
        long long mMax = 4001;
        long long mMin = 0;
        long long aMax = 4001;
        long long aMin = 0;
        long long sMax = 4001;
        long long sMin = 0;
        for (Rule r : wf.rulesV) {
            if (!r.onlyTarget)
                // cout << r.target << " " << r.prop << r.rule << r.value << " ";
                switch (r.prop) {
                    case 'x':
                        if (r.rule == '>') {
                            if (xMin < r.value) {
                                xMin = r.value;
                            }
                        } else {
                            if (xMax > r.value) {
                                xMax = r.value;
                            }
                        }
                        break;

                    case 'm':
                        if (r.rule == '>') {
                            if (mMin < r.value) {
                                mMin = r.value;
                            }
                        } else {
                            if (mMax > r.value) {
                                mMax = r.value;
                            }
                        }
                        break;
                    case 'a':
                        if (r.rule == '>') {
                            if (aMin < r.value) {
                                aMin = r.value;
                            }
                        } else {
                            if (aMax > r.value) {
                                aMax = r.value;
                            }
                        }
                        break;
                    case 's':
                        if (r.rule == '>') {
                            if (sMin < r.value) {
                                sMin = r.value;
                            }
                        } else {
                            if (sMax > r.value) {
                                sMax = r.value;
                            }
                        }
                        break;
                    default:
                        break;
                }
        }
        // cout << endl;
        // cout << xMin << "<x<" << xMax << " " << mMin << "<m<" << mMax << " " << sMin << "<s<" << sMax << " " << aMin << "<a<" << aMax << " " << endl;
        if (xMin > xMax || mMin > mMax || aMin > aMax || sMin > sMax) {
            cout << "Edge case detected!" << endl;
            break;
        }
        part2 += (xMax - xMin - 1) * (mMax - mMin - 1) * (aMax - aMin - 1) * (sMax - sMin - 1);
    }
    cout << part2 << endl;
}