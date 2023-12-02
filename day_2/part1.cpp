#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

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
    }
    cout << "the result is: " << sum << endl;
}
