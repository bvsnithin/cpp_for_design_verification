//https://www.hackerrank.com/challenges/variable-sized-arrays/problem?isFullScreen=true

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,q;
    cin >> n >> q;
    vector<vector<int>> arrays(n);
    for(int i =0;i<n;i++){
        int size;
        cin >> size;
        for(int j = 0;j<size;j++){
            int num;
            cin >> num;
            arrays[i].push_back(num);
        }
    }
    
    for(int i = 0;i<q;i++){
        int array_index, index;
        cin >> array_index >> index;
        cout << arrays[array_index].at(index) << endl;
    }
    return 0;
}