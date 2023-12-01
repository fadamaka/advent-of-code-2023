#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    ifstream is("data.txt");
    istream_iterator<string> start(is), end;
    vector<string> lines(start, end);
    cout << "Read " << lines.size() << " lines" << endl;

    // print the lines to stdout
    cout << "lines read in:\n";
    copy(lines.begin(), lines.end(),
         ostream_iterator<string>(cout, "\n "));
    cout << endl;
}