/* 
:::::::::::::: LOOPING ::::::::::::::
Loops are used to execute a block of code repeatedly as long as a specified condition is met.

1) For Loop         -> Used when you know exactly how many times you want to loop.
2) While Loop       -> Loops through a block of code as long as a specified condition is true.
3) Do-While Loop    -> Executes the code block once before checking the condition.
4) Range-based For  -> Specifically designed to iterate through elements of a collection/array.
5) Break & Continue -> Control flow statements within loops.
*/

#include <iostream>

using namespace std;

int main(){

    // ::::::::: FOR LOOP :::::::::
    for(int i = 0; i < 5; i++) {
        cout << "Iteration: " << i << endl;
    }
    cout << endl;

    // ::::::::: WHILE LOOP :::::::::
    
    int count = 0;
    while(count < 3) {
        cout << "Count: " << count << endl;
        count++;
    }
    cout << endl;

    // ::::::::: DO-WHILE LOOP :::::::::

    int num = 5;
    do {
        cout << "Runs at least once, num is: " << num << endl;
        num++;
    } while(num < 5);
    cout << endl;

    // ::::::::: RANGE-BASED FOR LOOP :::::::::

    int numbers[] = {10, 20, 30, 40, 50};
    for(int n : numbers) {
        cout << "Number: " << n << endl;
    }
    cout << endl;

    // ::::::::: BREAK & CONTINUE :::::::::

    for(int i = 0; i < 10; i++) {
        if(i == 3) {
            continue; // Skip the rest of this iteration
        }
        if(i == 7) {
            break; // Terminate the loop completely
        }
        cout << "i = " << i << endl;
    }
    cout << endl;

    return 0;
}
