#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
string replaceFirstNumber(string str) {
    string nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 3; i <= str.length(); i++) {
        string subStr = str.substr(0, i);
        for (int j = 0; j < 9; j++) {
            if (subStr.find(nums[j]) != string::npos) {
                cout << "found " << nums[j] << " at " << subStr.find(nums[j]) << endl;
                return str.replace(subStr.find(nums[j]), nums[j].length(), to_string(j + 1));
            }
        }
    }
    return str;
}

string replaceLastNumber(string str) {
    string nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = str.size() - 3; i >= 0; i--) {
        string subStr = str.substr(i, str.size() + 1);
        for (int j = 0; j < 9; j++) {
            if (subStr.find(nums[j]) != string::npos) {
                cout << "found " << nums[j] << " at " << str.length() - subStr.length() << endl;
                return str.replace(str.length() - subStr.length(), nums[j].length(), to_string(j + 1));
            }
        }
    }
    return str;
}

int getFirstNumber(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (int(str[i]) > 48 && int(str[i]) < 58) {
            return int(str[i]) - 48;
        }
    }
    return 0;
}
int getLastNumber(string str) {
    for (int i = str.length() - 1; i >= 0; i--) {
        if (int(str[i]) > 48 && int(str[i]) < 58) {
            return int(str[i]) - 48;
        }
    }
    return 0;
}
int main() {
    ifstream is("data.txt");
    istream_iterator<string> start(is), end;
    vector<string> lines(start, end);
    cout << "Read " << lines.size() << " lines" << endl;

    // print the lines to stdout
    cout << "\n lines read in:";
    int sum = 0;
    for (string str : lines) {
        cout << "\n str = " << str << endl;

        string fStr = replaceFirstNumber(str);

        string bStr = replaceLastNumber(str);

        int number = 0;
        number += getFirstNumber(fStr) * 10;

        number += getLastNumber(bStr);

        cout << "the number is " << number << endl;
        sum += number;
    }
    cout << "the result is: " << sum << endl;
    cout.flush();
}
