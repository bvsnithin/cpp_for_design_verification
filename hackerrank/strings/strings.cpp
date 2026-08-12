// https://www.hackerrank.com/challenges/c-tutorial-strings/problem?isFullScreen=true

#include <iostream>
#include <string>
using namespace std;

int main() {
	// Complete the program
    string a, b;
    
    // Take two inputs
    cin >> a;
    cin >> b;
    
    cout << a.size() << " " << b.size() << endl;
    cout << a+b << endl;
    
    string a_bar = b[0] + a.substr(1,a.length());
    string b_bar = a[0] + b.substr(1, b.length());
    cout << a_bar << " " << b_bar << endl;
    return 0;
}