#include <iostream>
#include <string>

// Function syntax 
/* 
return_type name_of_the_function(parameter_type parameter_name){
    return value;
}
*/

// Function Declaration. Sometimes also called as a prototype
// It tells the complier the function name and signature before it is used.
int addNums(int a, int b);

void passByValue(int x);

void passByReference(int& x);

void passByConstReference(const std::string& msg);

void passByPointer(int* x);
// This is called the function implementation. However, if the main function wants to use the function addNums
// we need to add the declaration as well. 
int addNums(int a, int b){
    return a+b;
}

// Main is the important function that is needed in any executable program
int main(){
    
    // Example of function call
    std::cout << "Sum of 10 and 20 = " << addNums(10,20) << std::endl;
    
    // Example of pass by value
    int x = 10;
    passByValue(x);
    std::cout << "Value of x is: "<< x << std::endl;

    // Example of pass by reference
    x = 25;
    passByReference(x);
    std::cout << "Value of x is: "<< x << std::endl;

    // Example of pass by const ref
    std::string message = "hello world!";
    passByConstReference(message);

    // Example of pass by pointer
    int* pointer_x = &x;
    passByPointer(pointer_x);
    std::cout<< "Value of x is: " << x << std::endl;

    return 0;
}


/*::::::::::: PARAMETER PASSING :::::::::::*/
/*
In cpp we have control over how arguments are passed into a function

1) Pass by value (This is default for primitive types, a copy of the argument is created and passed)
2) Pass by reference (This uses the "&" operator, passing the original variable itself)
3) Pass by const reference (Passed reference variable cannot be modified, "const" is used along with "&")
4) Pass by pointer (Similar to reference but we can set it to nullptr)
*/

/*
::::::::::: PASS BY VALUE :::::::::::

If a variable resides at address 0x100, passing it by value allocates a new block of memory (e.g., at 0x200), 
copies the data into 0x200, and runs all function operations exclusively on 0x200. 
The original at 0x100 remains untouched.

A full copy of the variable's value is created on the call stack at a brand-new memory address.

Pass by value is is best for small primitives like int, float, char, bool where copying is fast and cheap.

Syntax: void func(int a)
*/

void passByValue(int x){
    x = x+1;
}

/*
::::::::::: PASS BY REFERENCE :::::::::::
Syntax: void func(int& a)

Call:
int x = 25;
func(x);

Since this is a pass by reference in the function call, the address of x is pushed to function call and not value 25. 
Hence the operation in the function are performed and modifies the value at the address.

When you write a = a + 1;, 
the C++ compiler reads that reference and automatically generates CPU instructions that translate to: Value at addr x100 = Value at addr x100 + 1
*/
void passByReference(int& a){
    a = a + 1;
}

/*
::::::::::: PASS BY CONST REFERENCE :::::::::::
Syntax: void func(const int& a)

This is passing by referene with read only!
Keyword "const" keeps the function from modifying the original variable. 

Useful when passing large objects, string, or vectors are copies are avoided.
*/
void passByConstReference(const std::string& msg){
    // msg = "New" // This will give error as msg is readonly
    std::cout << msg << std::endl;
}

/*
::::::::::: PASS BY POINTER :::::::::::

Syntax: void func(int* a);

In this we pass the pointer as the input and the pointer can be pointing to null. 
Hence it needs to checked for null ptr
*/

void passByPointer(int* a){
    if(a!=nullptr){
        *a = *a + 1;
    }
}


