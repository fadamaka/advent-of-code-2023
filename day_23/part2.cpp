#include <..\utils\aoc.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<string> crossroads;

vector<pair<int, int>> directions = {pair<int, int>(-1, 0), pair<int, int>(1, 0), pair<int, int>(0, -1), pair<int, int>(0, 1)};
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
    for (auto&& i : directions) {
        int x = pos.first + i.first;
        int y = pos.second + i.second;
        if (crossroads[x][y] == '.' && visited.find(pair<int, int>(x, y)) == visited.end()) {
            pos = pair<int, int>(x, y);
            visited.insert(pos);
            counter++;
            return walkToCrossroad(visited, pos, counter);
        } else {
            if (crossroads[x][y] == 'x' && visited.find(pair<int, int>(x, y)) == visited.end()) {
                counter++;
                pos = pair<int, int>(x, y);
                return counter;
            }
        }
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

    for (auto&& i : crossroads) {
        myfile << i << endl;
    }
    pair<int, int> firstX = pair<int, int>(1, 1);
    set<pair<int, int>> firstVisited;
    firstVisited.insert(pair<int, int>(0, 1));
    firstVisited.insert(firstX);
    cout << "first x distance:" << walkToCrossroad(firstVisited, firstX, 1) << endl;
    cout << "first x pos:" << firstX.first << " " << firstX.second << endl;
    myfile.close();
    cout << crossroads[x][y] << endl;
    for (auto&& i : directions) {
        cout << crossroads[x + i.first][y + i.second] << endl;
        if (crossroads[x + i.first][y + i.second] == '.') {
            pair<int, int> pos = pair<int, int>(x + i.first, y + i.second);
            set<pair<int, int>> visited;
            visited.insert(pair<int, int>(x, y));
            visited.insert(pos);
            cout << walkToCrossroad(visited, pos, 1) << " " << pos.first << " " << pos.second << endl;
        }
    }
}