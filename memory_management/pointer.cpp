#include <iostream>
using namespace std;
// Pointer is a special type of variable in c/cpp that holds address of another variable
// int* -> This is an integer pointer variable 
// double* -> This is a double pointer variable
// Both int* and double* are 8 bytes in size


int main(){
    int a = 50;
    int* addr_a = &a;
    double b = 79.0;
    double* addr_b = &b;
    cout << "Size of pointer a: " << sizeof(addr_a) << endl;
    cout << "Size of pointer b: " << sizeof(addr_b) << endl;

    // Dereferencing
    cout << "Value of a previously: "<< a << endl;
    *addr_a = 60; //This is dereferencing. This line modifies the value at the address stored in addr_a
    cout << "Value of a is now: "<< a << endl;

    // Printing address using the & operator
    cout << "Address of a (&a): " << &a << endl;
    cout << "Value stored in addr_a: " << addr_a << endl; // Same as &a

    // Null pointer
    int* empty_ptr = nullptr; //

    if (empty_ptr != nullptr) {
        cout << *empty_ptr << endl;
    } else {
        cout << "empty_ptr is safe: points to nothing!" << endl;
    }

    // Pointer arithmetic
    // When we add 1 to pointer, it does not jump by 1 byter, but rather jumps by sizeof(type) bytes
    int int_a = 10;
    double double_a = 10.0;

    addr_a = &int_a;
    double* addr_double_a = &double_a;

    cout << endl;

    cout << "Address of int_a (&int_a): " << addr_a << " Value of int_a: " << *addr_a << endl;
    cout << "Address of double_a (&double_a): " << addr_double_a << " Value of double_a: " << *addr_double_a << endl;
    cout  << endl;
    // Adding 1 to pointers
    addr_a = addr_a +1;              // This will add 4 bytes, because size of int is 4 bytes
    addr_double_a = addr_double_a+1; // This will add 8 bytes, because size of int is 8 bytes

    cout << "Address of int_a (&int_a): " << addr_a << " Value of int_a: " << *addr_a << endl;
    cout << "Address of double_a (&double_a): " << addr_double_a << " Value of double_a: " << *addr_double_a << endl;

    // Pointer arithmetic with arrays
    int arr[3] = {12,54,89};
    int* ptr = arr; //This points to the base address arr[0]

    cout << *ptr << endl; // Prints arr[0]
    cout << *(ptr+1) << endl; // Prints arr[1]
    cout << *(ptr+2) << endl; //Prints arr[2]

}