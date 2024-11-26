#include <..\utils\aoc.h>

#include <fstream>
#include <iostream>
#include <map>
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
        if (x < 0) {
            return 0;
        }
        if (x > crossroads.size() - 1) {
            return 0;
        }
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

int** fillEdgeMatrix(map<pair<int, int>, int> nodeMap) {
    int** arr = new int*[nodeMap.size()];
    for (int i = 0; i < nodeMap.size(); ++i) {
        arr[i] = new int[nodeMap.size()];
        for (int j = 0; j < nodeMap.size(); ++j) {
            arr[i][j] = 0;
        }
    }
    for (auto&& n : nodeMap) {
        int x = n.first.first;
        int y = n.first.second;
        for (auto&& i : directions) {
            // cout << crossroads[x + i.first][y + i.second] << endl;
            if (crossroads[x + i.first][y + i.second] == '.') {
                pair<int, int> pos = pair<int, int>(x + i.first, y + i.second);
                set<pair<int, int>> visited;
                visited.insert(pair<int, int>(x, y));
                visited.insert(pos);
                int edge = walkToCrossroad(visited, pos, 1);
                if (edge != 0)
                    arr[n.second][nodeMap.find(pos)->second] = edge;
            }
        }
    }

    return arr;
}

int** copyArray(int** orig, int size) {
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            arr[i][j] = orig[i][j];
        }
    }
    return arr;
}

int** deleteNodes(int** input, int size, int nodeId) {
    for (int i = 0; i < size; ++i) {
        input[i][nodeId] = 0;
        input[nodeId][i] = 0;
    }
    return input;
}

void walkAll(int** edgeMatrix, int size, int nodeId, int count, int& result, int endId) {
    int counter = 0;
    // cout << nodeId << endl;
    for (int i = 0; i < size; ++i) {
        if (edgeMatrix[nodeId][i] > 0) {
            int edgeWeight = edgeMatrix[nodeId][i];
            walkAll(deleteNodes(copyArray(edgeMatrix, size), size, nodeId), size, i, count + edgeWeight, result, endId);
            counter++;
        }
    }
    if (counter == 0) {
        if (count > result) {
            if (nodeId == endId) {
                result = count;
            }
        }
    }
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

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
    map<pair<int, int>, int> nodeMap;

    for (int i = 1; i < crossroads.size() - 1; i++) {
        for (int j = 1; j < crossroads[i].size() - 1; j++) {
            if (crossroads[i][j] == 'x') {
                Node node = Node(count, i, j);
                nodeMap.insert(pair<pair<int, int>, int>(pair<int, int>(i, j), count));
                count++;
                cout << node << endl;
            }
        }
    }

    int** edgeMatrix;
    edgeMatrix = fillEdgeMatrix(nodeMap);
    for (int i = 0; i < nodeMap.size(); ++i) {
        for (int j = 0; j < nodeMap.size(); ++j) {
            cout << edgeMatrix[i][j] << " ";
        }
        cout << endl;
    }
    // for (int i = 0; i < nodeMap.size() - 1; i++) {
    //     for (int j = 0; j < nodeMap.size() - 1; j++) {
    //         edgeMatrix[i][j] = 0;
    //     }
    // }

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
    int firstDistance = walkToCrossroad(firstVisited, firstX, 1);
    cout << "first x distance:" << firstDistance << endl;
    cout << "first x pos:" << firstX.first << " " << firstX.second << endl;
    cout << "first x ID:" << nodeMap.find(firstX)->second << endl;

    pair<int, int> lastX = pair<int, int>(lines.size() - 2, lines.size() - 2);
    set<pair<int, int>> lastVisited;
    lastVisited.insert(pair<int, int>(lines.size() - 1, lines.size() - 2));
    lastVisited.insert(lastX);
    int lastDistance = walkToCrossroad(lastVisited, lastX, 1);
    cout << "last x distance:" << lastDistance << endl;
    cout << "last x pos:" << lastX.first << " " << lastX.second << endl;
    cout << "last x ID:" << nodeMap.find(lastX)->second << endl;
    cout << "add to longest: " << firstDistance + lastDistance << endl;
    myfile.close();

    int result = 0;
    walkAll(edgeMatrix, nodeMap.size(), nodeMap.find(firstX)->second, firstDistance + lastDistance, result, nodeMap.find(lastX)->second);
    cout << "result: " << result << endl;
}

/*
create recursive solution that branches out and takes all paths, it passes down the the adjactency matrix and removes the edges of visited nodes, when reaches end node or gets to a dead end terminates

dead end = 0
end node = sum(weights)

*/