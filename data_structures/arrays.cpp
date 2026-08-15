/* 
:::::::::::::: ARRAYS ::::::::::::::
Array: It is a contiguous block of memory that stores fixed size sequence of elements of the same type

1) Contiguous -> Items are stored one after another in an unbroken, sequential chain within memory.
2) Fixed Size -> Size of the array must be known at the compile time and should not change during execution
3) Same type  -> Homogenous, meaning all elements are of same type(array of int, array os string)
*/

#include <iostream>
#include <string>

using namespace std;

void modifyArray(int arr[], int size){
    for(int i = 0;i<size;i++){
        arr[i] = arr[i]+100;
    }
}

void printArray(int arr[], int size){
    for(int i = 0;i<size;i++){
        cout << arr[i] << endl;
    }
    cout << endl;
}

int main(){
    
    // ::::::::: Declaration :::::::::
    int scores[5];     // Syntax: type name[size];
    string names[5];   // Array of strings
 
    // ::::::::: Initialization (Element by Element) :::::::::
    // Once we declare a raw array, we cannot assign values to the entire array at once. 
    // We need to do element by element assignment.
    scores[0] = 10;
    scores[1] = 12;
    scores[2] = 15;
    scores[3] = 8;
    scores[4] = 9;
 
    names[0] = "Alice";
    names[1] = "Borris";
    names[2] = "Cynthia";
    names[3] = "Diego";
    names[4] = "Esha";
 
    // ::::::::: Declaration and Initialization :::::::::
    int ages[3] = {10,12,39};
    string products[5] = {"pepsi", "kellogs", "nestle", "cola", "cadbury"};
 
    // Partial initialization (remaining elements automatically set to 0)
    int counts[5] = {10, 20}; // {10, 20, 0, 0, 0}
 
    // Zero-initialization
    int zeros[5] = {}; // {0, 0, 0, 0, 0}
 
    // Implicit size deduction
    int primes[] = {2, 3, 5, 7, 11}; // Size inferred as 5

    // ::::::::: ACCESSING ELEMENTS :::::::::
    cout << ages [0] << " " << ages[1] << " " << ages[2] << endl; // 10 12 39

    // ::::::::: POINTERS :::::::::

    // An array name decays to a pointer to its first element
    int* ptr = ages; 

    cout << "Memory address of arr[0] via &arr[0]: " << &ages[0] << endl;
    cout << "Memory address of arr[0] via arr:     " << ages << endl;
    cout << "Memory address via pointer variable:  " << ptr << endl << endl;

    // Accessing the array element by dereferencing the pointer
    cout << "First Element of ages = " << *ptr << endl;
    cout << "Second Element of ages = " << *(ptr+1) << endl;
    cout << "Third Element of ages = " << *(ptr+2) << endl << endl;
    
    // Modifying the array to add 100 to each value
    modifyArray(ages, 3);
    printArray(ages, 3);

    // ::::::::: 2D ARRAYS :::::::::
    int mat[3][3] = {
        {1,2,3},
        {4,5,6}
    };

    for(int rows = 0;rows < 3; rows++){
        for(int cols = 0; cols < 3; cols++){
            cout << mat[rows][cols] << " ";
        }
        cout << endl;
    }
    return 0;
}