#include <..\utils\aoc.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<string> crossroads;

struct Node {
    int id;
    int x;
    int y;

    Node(int id, int x, int y) {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};
ostream& operator<<(ostream& os, const Node& node) {
    os << "ID: "
       << node.id
       << " x: "
       << node.x
       << " y: "
       << node.y;
    return os;
}

int walkToCrossroad(set<pair<int, int>> visited, pair<int, int>& pos, int counter) {
    int x = pos.first;
    int y = pos.second;
    if (crossroads[x][y] == '.' && visited.find(pair<int, int>(x, y)) == visited.end()) {
        pos = pair<int, int>(x, y);
        return counter;
    } else {
        counter++;
    }
    return 0;
}

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

    for (auto&& i : cleaned) {
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
    int count = 0;
    vector<Node> nodes;
    for (int i = 1; i < crossroads.size() - 1; i++) {
        for (int j = 1; j < crossroads[i].size() - 1; j++) {
            if (crossroads[i][j] == 'x') {
                Node node = Node(++count, i, j);
                cout << node << endl;
            }
        }
    }

    int edgeMatrix[lines.size() - 1][lines[0].size() - 1];
    bool end = false;
    int x = 3;
    int y = 11;
    while (!end) {
    }
    for (auto&& i : crossroads) {
        myfile << i << endl;
    }
    myfile.close();
}