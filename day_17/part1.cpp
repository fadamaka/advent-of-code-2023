#include <..\utils\aoc.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
int recCount = 0;
enum direction {
    N,
    S,
    W,
    E,
    O
};

struct Node {
    int weight;
    direction dir;
    int step;
    int shortest;
    Node(int input) {
        weight = input;
        dir = O;
        step = 0;
        shortest = INT_MAX;
    }
    Node(){};
};

vector<vector<Node>> nodeMatrix;
void calculatePath(int y, int x);
void checkNode(Node current, int loopY, int loopX, direction targetDir, int& targetY, int& targetX, int& targetShortest) {
    Node targetNode = nodeMatrix[loopY][loopX];
    if (current.shortest + targetNode.weight <= targetNode.shortest) {
        nodeMatrix[loopY][loopX].shortest = current.shortest + targetNode.weight;
        nodeMatrix[loopY][loopX].dir = targetDir;
        if (targetDir == current.dir) {
            nodeMatrix[loopY][loopX].step = current.step + 1;
        } else {
            nodeMatrix[loopY][loopX].step = 1;
        }
        if (current.shortest + targetNode.weight < targetShortest) {
            targetShortest = current.shortest + targetNode.weight;
            targetY = loopY;
            targetX = loopX;
        }
        calculatePath(loopY, loopX);
    }
}

void calculatePath(int y, int x) {
    cout << recCount++ << " " << y << ":" << x << endl;
    Node current = nodeMatrix[y][x];
    set<direction> allowedDir;
    int targetShortest = INT_MAX;
    int targetY = 0;
    int targetX = 0;
    if (current.dir == N || current.dir == S) {
        allowedDir = {W, E};
    }
    if (current.dir == E || current.dir == W) {
        allowedDir = {N, S};
    }
    if (current.step < 3) {
        allowedDir.insert(current.dir);
    }
    if (current.dir == O) {
        allowedDir = {N, S, W, E};
    }
    Node targetNode;
    for (direction d : allowedDir) {
        int loopY = y;
        int loopX = x;
        if (d == N && y > 0) {
            checkNode(current, y - 1, x, d, targetY, targetX, targetShortest);
        }
        if (d == S && y < nodeMatrix.size() - 1) {
            checkNode(current, y + 1, x, d, targetY, targetX, targetShortest);
        }
        if (d == W && x > 0) {
            checkNode(current, y, x - 1, d, targetY, targetX, targetShortest);
        }
        if (d == E && x < nodeMatrix[y].size() - 1) {
            checkNode(current, y, x + 1, d, targetY, targetX, targetShortest);
        }
    }
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    cout << "as" << endl;
    transform(lines.begin(), lines.end(), back_inserter(nodeMatrix), [](const string& str) { 
        vector<Node> row;
        transform(str.begin(),str.end(), back_inserter(row),[](const char& ch){
            return Node(int(ch)-48);});
        return row; });
    nodeMatrix[0][0].shortest = 0;
    calculatePath(0, 0);
    // for (auto&& i : nodeMatrix) {
    //     for (auto&& j : i) {
    //         cout << setw(3) << j.shortest << " ";
    //     }
    //     cout << endl;
    // }
    cout << nodeMatrix[nodeMatrix.size() - 1][nodeMatrix[0].size() - 1].shortest;
}