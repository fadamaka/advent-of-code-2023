#include <..\utils\aoc.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

vector<long long> getNumbers(string subject);
long long getLong(string subject);

long long findTime(long long time, long long distance);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    vector<long long> times = getNumbers(lines.at(0));
    vector<long long> distances = getNumbers(lines.at(1));
    cout << findTime(times.at(0), distances.at(0)) * findTime(times.at(1), distances.at(1)) * findTime(times.at(2), distances.at(2)) * findTime(times.at(3), distances.at(3)) << endl;
    cout << findTime(getLong(lines.at(0)), getLong(lines.at(1))) << endl;
}

vector<long long> getNumbers(string subject) {
    vector<long long> result;
    try {
        std::regex re("\\d+");
        std::sregex_iterator next(subject.begin(), subject.end(), re);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            result.push_back(stol(match.str()));
            next++;
        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
    }
    return result;
}

long long getLong(string subject) {
    string result;
    try {
        std::regex re("\\d+");
        std::sregex_iterator next(subject.begin(), subject.end(), re);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            result += match.str();
            next++;
        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
    }
    return stoll(result);
}

long long findTime(long long time, long long distance) {
    long long result;
    for (long long i = 0; i < time / 2; i++) {
        if (i * (time - i) > distance) {
            result = time - 2 * i + 1;
            break;
        }
    }
    return result;
}