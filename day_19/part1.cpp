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

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    unordered_map<string, Workflow> wfMap;
    vector<Part> parts;
    bool partsB = false;
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 0) {
            partsB = true;
            continue;
        }
        if (!partsB) {
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
        } else {
            vector<string> partProps = splitByChar(lines[i].substr(1, lines[i].size() - 2), ',');
            parts.push_back(Part(partProps[0].substr(2), partProps[1].substr(2), partProps[2].substr(2), partProps[3].substr(2)));
        }
    }
    int result = 0;
    for (Part p : parts) {
        string targetWf = "in";
        while (true) {
            if (targetWf == "A") {
                result += p.getSum();
                break;
            }
            if (targetWf == "R") {
                break;
            }
            Workflow wf = wfMap.find(targetWf)->second;
            for (Rule r : wf.rulesV) {
                if (r.onlyTarget) {
                    targetWf = r.target;
                } else {
                    if (p.invoke(r.prop, r.value, r.rule)) {
                        targetWf = r.target;
                        break;
                    }
                }
            }
        }
    }

    cout << result << endl;
}