#include <..\utils\aoc.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long calculateAnswer(int input) {
    long long n = (input - 65) / 131 + 1;
    cout << n << endl;
    return 14773LL * pow(n, 2LL) - 14683LL * n + 3640LL;
}
int main() {
    cout << calculateAnswer(65) << endl;
    cout << calculateAnswer(196) << endl;
    cout << calculateAnswer(327) << endl;
    cout << calculateAnswer(458) << endl;
    cout << calculateAnswer(589) << endl;
    cout << calculateAnswer(720) << endl;
    cout << calculateAnswer(1244) << endl;
    cout << calculateAnswer(1375) << endl;
    cout << calculateAnswer(1506) << endl;
    cout << calculateAnswer(26501365) << endl;
}