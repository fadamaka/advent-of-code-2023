
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> readFileIntoVector(string fileName) {
    string str;
    vector<string> lines;

    fstream file;
    file.open(fileName, ios::in);

    while (getline(file, str)) {
        lines.push_back(str);
    }
    return lines;
}

vector<string> splitByChar(string str, char ch) {
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == ch || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}