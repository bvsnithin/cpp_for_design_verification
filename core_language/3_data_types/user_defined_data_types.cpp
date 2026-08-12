#include <iostream>
#include <ostream>
#include <string>
using namespace std;
// User defined data types allow us to create custom types by grouping primitive data types together
// Struct and Enum are two ways of creating user defined data types

// ::::::: STRUCT :::::::
// Struct is basically short for structures
// Struct is an aggreagrate of multiple data types into a single memory layout
// By default all the members of a struct are public
// However, we can use access specifiers like public, private, and protected like inside a class for restriction
// Structs in cpp can also have constructors and destructors. Also member functions

struct Player{
    string name;
    int age;
    double health; 
};

// ::::::: ENUMS :::::::
// Enum is short for Enumeration
// There are two styles to enums - unscoped and scoped 
// Unscoped are from traditional C and they are created using keyword "enum"
// Scoped are introducded in cpp 11 and they are created using enum class

enum Status{
    Pending,  // 0
    Approved, // 1
    Rejected  // 2
};

// Using cpp enum class to create enums
// char is the underlying type of the OrderStatus. By default it's int
enum class OrderStatus : char{
    Ordered = 'O',
    Processing = 'P',
    Delivered = 'D'
};

int main(){
    // Instantiation
    Player player1{"Harry Kane", 34,85.5};
    cout << player1.name << endl;
    cout << player1.age << endl;
    

    Status s = Approved;
    cout << "Value of s is: " << s << endl; // This will print 1 
    // Enum creates a set of named integral constants
    s = Rejected;
    cout << "Value of s is: " << s << endl; // This will print 2
    cout << "Size of s is : " << sizeof(s) << endl;  // Prints 4
    double double_s = static_cast<double>(s);
    cout << "Size of s is : " << sizeof(double_s) << endl;  // Prints 8

    // Scoped enum
    OrderStatus status = OrderStatus::Processing;

    cout << "Order status is: " << static_cast<char>(status) << endl;

    status = OrderStatus::Ordered;
    cout << "Order status is: " << static_cast<char>(status) << endl; 
    
    return 0;
}



