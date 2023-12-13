#include <..\utils\aoc.h>
#include <math.h>

#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <thread>
#include <vector>

using namespace std;

bool entryValidator(string task, string input);
pair<string, vector<int>> inputParser(string str, int j);

#define K 19

// DP lookup table

// Function to find all combinations k-bit numbers with
// n-bits set where 1 <= n <= k
vector<string> findBitCombinations(int k, int hashtags, vector<int> v);
vector<string> continueCombinations(string combo);

long long workFunc(pair<string, vector<int>> p, vector<string>::iterator begin, vector<string>::iterator end);

string replaceMarks(string input, string str);
int countQuestionMarks(string str);
int countQuestionTags(string str);

string unpack(string str, vector<int> v);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<pair<string, vector<int>>> parsedLines;
    transform(lines.begin(), lines.end(), back_inserter(parsedLines), [](const string& str) { return inputParser(str, 0); });

    vector<pair<string, vector<int>>> parsedLinesPt2;
    transform(lines.begin(), lines.end(), back_inserter(parsedLinesPt2), [](const string& str) { return inputParser(str, 1); });

    // for (string str : findBitCombinations(7, 5, {1, 1, 3})) {
    //     cout << unpack(str, {1, 1, 3}) << endl;
    // }
    long long result = 0;
    int skip = 0;
    int blacksheep = 0;

    for (int i = skip; i < parsedLines.size(); i++) {
        int markCount2 = 0;
        int tagCount2 = 0;
        int countTags2 = 0;
        try {
            pair<string, vector<int>> p = parsedLines[i];
            pair<string, vector<int>> p2 = parsedLinesPt2[i];
            // cout << p.first;
            // for (int i : p.second) {
            //     cout << " " << i;
            // }
            // cout << endl;

            // cout << p2.first;
            // for (int i : p2.second) {
            //     cout << " " << i;
            // }
            // cout << endl;
            int markCount = countQuestionMarks(p.first);
            int tagCount = countQuestionTags(p.first);
            int countTags = accumulate(p.second.begin(), p.second.end(), 0);
            // cout << "?: " << markCount << endl;
            vector<string> combos = findBitCombinations(p.first.size(), countTags, p.second);
            // cout << "combinations: " << combos.size() << endl;
            long long valid = 0;
            for (string str : combos) {
                if (entryValidator(p.first, unpack(str, p.second))) {
                    valid++;
                }
            }
            combos.clear();
            combos.shrink_to_fit();
            markCount2 = countQuestionMarks(p2.first);
            tagCount2 = countQuestionTags(p2.first);
            countTags2 = accumulate(p2.second.begin(), p2.second.end(), 0);
            // cout << "?: " << markCount << endl;
            vector<string> combos2 = findBitCombinations(p2.first.size(), countTags2, p2.second);
            // cout << i + 1 << " combinations: " << combos2.size() << endl;

            int threadCount = 32;

            vector<future<long long>> futureLongs;
            // vector<vector<string>> sV;
            // sV.push_back(v1);
            long long valid2 = 0;
            int yep = 0;
            if (combos2.size() < 10000000) {
                for (string str : combos2) {
                    if (entryValidator(p2.first, unpack(str, p2.second))) {
                        valid2++;
                    }
                }
            } else {
                cout << "async" << endl;

            startover:
                futureLongs.push_back(async(&workFunc, p2, combos2.begin(), combos2.begin() + (combos2.size() / threadCount)));
                for (size_t j = 1; j < threadCount - 1; j++) {
                    futureLongs.push_back(async(&workFunc, p2, combos2.begin() + (combos2.size() / threadCount) * j, combos2.begin() + (combos2.size() / threadCount) * (j + 1)));
                    // sV.push_back(v2);
                }

                futureLongs.push_back(async(&workFunc, p2, combos2.begin() + (combos2.size() / threadCount) * (threadCount - 1), combos2.end()));

                // sV.push_back(v8);
                for (int i = 0; i < futureLongs.size(); i++) {
                    valid2 += futureLongs[i].get();
                    // sV[i].clear();
                    // sV[i].shrink_to_fit();
                }
                futureLongs.clear();
                futureLongs.shrink_to_fit();
                if (combos2.size() == 100000000) {
                    cout << "yep: " << ++yep << endl;
                    string comboC = combos2[combos2.size() - 1];
                    combos2.clear();
                    combos2.shrink_to_fit();
                    combos2 = continueCombinations(comboC);
                    goto startover;
                }
            }
            combos2.clear();
            combos2.shrink_to_fit();
            if (valid2 % valid != 0) {
                cout << i + 1 << " black sheep found!" << endl;
                ++blacksheep;
            }
            // cout << i + 1 << ": " << valid2 << "/" << valid << "=" << valid2 / valid << " pow:" << pow(valid2 / valid, 4) << endl;
            long long subresult = valid * pow(valid2 / valid, 4);
            // cout << i + 1 << ": " << subresult << endl;
            result += subresult;
            // cout << "res: " << result << endl;
            //  if ((i + 1) % 10 == 0) {
            //      cout << (i + 1) / 10 << "%" << endl;
            //  }
            // break;
        } catch (const std::exception& e) {
            cout << e.what() << endl;
            cout << "i: " << i << " markcount: " << markCount2 << " tagcount: " << tagCount2 << " countags: " << countTags2 << endl;
            break;
        }
    }
    cout << blacksheep;
}

bool entryValidator(string task, string input) {
    if (task.size() != input.size()) {
        // cout << input << " false" << endl;

        return false;
    }
    for (int i = 0; i < task.size(); i++) {
        if (task[i] != '?' && task[i] != input[i]) {
            // cout << input << " false" << endl;
            return false;
        }
    }

    // cout << task << endl;
    // cout << input << " true" << endl;

    return true;
}

pair<string, vector<int>> inputParser(string str, int j) {
    vector<string> spaceSplit = splitByChar(str, ' ');
    vector<int> validatorNumbers;
    vector<string> validatorNumbersStr = splitByChar(spaceSplit[1], ',');
    transform(validatorNumbersStr.begin(), validatorNumbersStr.end(), back_inserter(validatorNumbers), [](const string& str) { return stoi(str); });
    string pt2 = spaceSplit[0];
    vector<int> validatorNumbersPt2 = validatorNumbers;
    for (int i = 0; i < j; i++) {
        pt2 += '?' + spaceSplit[0];
        validatorNumbersPt2.insert(validatorNumbersPt2.end(), validatorNumbers.begin(), validatorNumbers.end());
    }

    return pair<string, vector<int>>(pt2, validatorNumbersPt2);
}

vector<string> findBitCombinations(int k, int hashtags, vector<int> v) {
    string combo;
    vector<string> result;
    for (int i = 0; i < k - hashtags - v.size() + 1; i++) {
        combo += '.';
    }
    for (int i = 0; i < v.size(); i++) {
        combo += '#';
    }
    result.push_back(combo);

    while (combo.find(".#") != string::npos) {
        int rfound = combo.rfind(".#");
        if (rfound == combo.rfind(".##")) {
            int count = 0;
            for (int i = rfound + 2; i < combo.size(); i++) {
                if (combo[i] == '#') {
                    count++;
                } else {
                    break;
                }
            }
            // cout << combo << " needs to pushback " << count << " #s" << endl;
            if ((rfound + 2 + count) != combo.size()) {
                // cout << "before pb: " << combo << endl;
                // cout << combo.substr(0, rfound + 2) << endl;
                // cout << combo.substr(rfound + 2 + count) << endl;
                // cout << combo.substr(rfound + 2, count) << endl;
                combo = combo.substr(0, rfound + 2) + combo.substr(rfound + 2 + count) + combo.substr(rfound + 2, count);

                // cout << "after pb: " << combo << endl;
            }
        }
        combo.replace(rfound, 2, "#.");
        result.push_back(combo);
        if (result.size() > 99999999) {
            return result;
        }
    }

    return result;
}

vector<string> continueCombinations(string combo) {
    vector<string> result;

    while (combo.find(".#") != string::npos) {
        int rfound = combo.rfind(".#");
        if (rfound == combo.rfind(".##")) {
            int count = 0;
            for (int i = rfound + 2; i < combo.size(); i++) {
                if (combo[i] == '#') {
                    count++;
                } else {
                    break;
                }
            }
            // cout << combo << " needs to pushback " << count << " #s" << endl;
            if ((rfound + 2 + count) != combo.size()) {
                // cout << "before pb: " << combo << endl;
                // cout << combo.substr(0, rfound + 2) << endl;
                // cout << combo.substr(rfound + 2 + count) << endl;
                // cout << combo.substr(rfound + 2, count) << endl;
                combo = combo.substr(0, rfound + 2) + combo.substr(rfound + 2 + count) + combo.substr(rfound + 2, count);

                // cout << "after pb: " << combo << endl;
            }
        }
        combo.replace(rfound, 2, "#.");
        result.push_back(combo);
        if (result.size() > 99999999) {
            return result;
        }
    }

    return result;
}

string replaceMarks(string input, string str) {
    int count = 0;
    string newString = input;
    for (int i = 0; i < input.size(); i++) {
        if (newString[i] == '?') {
            newString[i] = str[count];
            count++;
        }
    }
    return newString;
}

int countQuestionMarks(string str) {
    int count = 0;
    for (char ch : str) {
        if (ch == '?') {
            count++;
        }
    }
    return count;
}

int countQuestionTags(string str) {
    int count = 0;
    for (char ch : str) {
        if (ch == '#') {
            count++;
        }
    }
    return count;
}

long long workFunc(pair<string, vector<int>> p, vector<string>::iterator begin, vector<string>::iterator end) {
    long long valid2 = 0;
    for (vector<string>::iterator it = begin; it != end; it++) {
        if (entryValidator(p.first, unpack(*it, p.second))) {
            valid2++;
        }
    }

    return valid2;
}

string unpack(string str, vector<int> v) {
    // cout << "packed: " << str << endl;
    string result;
    int i = 0;
    for (char ch : str) {
        if (ch == '.') {
            result += ch;
        } else {
            if (i != 0) {
                result += '.';
            }
            for (int j = 0; j < v[i]; j++) {
                result += '#';
            }
            i++;
        }
    }
    return result;
}

// string iterateCombo(string input) {
// }