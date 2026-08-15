/* 
:::::::::::::: CONDITIONALS ::::::::::::::
Used to perform different actions based on different conditions.

1) If-Else    -> Executes a block of code if a condition is true.
2) Ternary    -> Short-hand representation of if-else.
3) Switch     -> Selects one of many code blocks to be executed.
*/

#include "iostream"
using namespace std;
int main(){

    // ::::::::: IF - ELSE :::::::::
    int score = 85;

    if(score>80){
        cout << "Score above 80" <<endl;
    }
    else if(score <80 && score > 60) {
        cout << "Score between 80 and 60" << endl;
    }
    else {
        cout << "Low score" << endl;
    }

    // ::::::::: TERNARY :::::::::
    int age = 20;
    string result = (age >= 18) ? "Adult" : "Minor"; // condition ? expression_if_true : expression_if_false
    cout << "Age status: " << result << endl;

    // ::::::::: SWITCH CASE :::::::::
    int day = 3;
    switch(day){
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        default:
            cout << "Weekend" << endl;
            break;
    }

    return 0;
}