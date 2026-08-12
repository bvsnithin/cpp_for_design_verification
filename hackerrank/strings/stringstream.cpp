//https://www.hackerrank.com/challenges/c-tutorial-stringstream/problem?isFullScreen=true

#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
	// Complete this function
    vector<int> output;
    stringstream ss(str);
    
    int number;
    char ch; //Consumes the ,(comma)
    while(ss >> number){
        output.push_back(number);
        ss >> ch;
    }
    return output;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}