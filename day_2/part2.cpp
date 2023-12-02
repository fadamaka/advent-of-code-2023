#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> customSplit(string str) {
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == ':' || str[i] == ',' || str[i] == ';' || str[i] == ':' || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

vector<string> splitBySpaces(string str) {
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            if (temp == "" || temp == "\n" || temp == " ")
                continue;
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

int main() {
    map<string, int> rulesMap = {{"red", 12}, {"green", 13}, {"blue", 14}};

    string str;
    vector<string> lines;

    fstream file;
    file.open("data.txt", ios::in);

    while (getline(file, str)) {
        lines.push_back(str);
    }
    int result = 0;

    for (int i = 0; i < lines.size(); i++) {
        map<string, int> valuesMap = {{"red", 0}, {"green", 0}, {"blue", 0}};

        cout << "game number " << i + 1 << " " << lines[i] << endl;
        vector<string> line = customSplit(lines[i]);
        line.erase(line.begin());
        for (string splits : line) {
            vector<string> values = splitBySpaces(splits);
            int num = stoi(values[0].erase(0, 1));
            string color = values[1];
            cout << "num:" << num << " color: " << color << " " << rulesMap.find(color)->second << endl;
            if (valuesMap.find(color)->second < num) {
                valuesMap.find(color)->second = num;
            }
        }
        int rowResult = 1;
        for (std::map<string, int>::iterator it = valuesMap.begin(); it != valuesMap.end(); ++it) {
            rowResult *= it->second;
        }
        cout << "row result: " << rowResult << endl;
        result += rowResult;
    }
    cout << "result: " << result << endl;
}
