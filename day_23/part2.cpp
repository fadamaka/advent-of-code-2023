#include <..\utils\aoc.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data2.txt");

    ofstream myfile;
    vector<string> cleaned;
    myfile.open("example.txt");
    for (int i = 0; i < lines.size(); i++) {
        string str;
        for (int j = 0; j < lines[i].size(); j++) {
            char output = lines[i][j] == '#' ? '#' : '.';
            str += (output);
        }
        cleaned.push_back(str);
    }
    vector<string> crossroads;
    for (auto &&i : cleaned) {
        crossroads.push_back(i);
    }

    for (int i = 1; i < cleaned.size() - 1; i++) {
        for (int j = 1; j < cleaned[i].size() - 1; j++) {
            if (cleaned[i][j] == '.') {
                int count = 0;
                if (cleaned[i - 1][j] == '.') {
                    count++;
                }
                if (cleaned[i + 1][j] == '.') {
                    count++;
                }
                if (cleaned[i][j - 1] == '.') {
                    count++;
                }
                if (cleaned[i][j + 1] == '.') {
                    count++;
                }
                if (count > 2) {
                    crossroads[i][j] = 'x';
                }
            }
        }
    }

    for (auto &&i : crossroads) {
        myfile << i << endl;
    }

    myfile.close();
}