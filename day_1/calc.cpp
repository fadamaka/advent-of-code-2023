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
    cout << "\n lines read in:";
    int sum = 0;
    for (string str : lines)
    {
        cout << "\n str = " << str << endl;
        bool first = true;
        int number = 0;
        for (int i = 0; i < str.length(); i++)
        {

            if (int(str[i]) > 48 && int(str[i]) < 58 && first)
            {
                cout << str[i] << " ";
                cout << int(str[i]) - 48 << " as num ";
                number += (int(str[i]) - 48) * 10;
                first = false;
            }
        }
        bool last = true;
        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (int(str[i]) > 48 && int(str[i]) < 58 && last)
            {
                cout << str[i] << " ";
                cout << int(str[i]) - 48 << " as num ";
                number += (int(str[i]) - 48);
                last = false;
            }
        }

        cout << "the number is " << number << endl;
        sum += number;
    }
    cout << "the result is:" << sum << endl;
}