#include <iostream>
// #include <print>
using namespace std;

int main()
{   
    // Using cout to print plain text
    cout << "Hello World";
    // The above line prints Hello World but it doesn't print a new lines afterwards
    // To print a new line after, we need to use \n or endl
    cout << "\nToday is a good day!\n";
    cout << "The city is doing well!" << endl;

    // Using cout to print a variable
    int age = 20;
    cout  << "Xavier is only " << age << " years old!" << endl;

    // In modern cpp, we have print along with cout
    // But print is part of the header file - print, so we need to include that!
    /*
    print("Hello World");
    std::print("{}", age);
    */

    // cpp can also use c style printf for printing
    printf("Hello World"); // This again doesn't print on the new lines
    printf("\nAustin is the capital of Texas\n");

    string name = "Nathan Ellis";
    cout << name << endl;
    return 0;
}