
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