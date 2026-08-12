#include <iostream>
#include <ostream>
#include <string>

using namespace std;

int main(){
    
    // Strings in cpp are not immutable, they are mutable
    // In java, python, c#, string when modified, will return a new object, but in cpp, string modification happen in place
    // Creating strings
    string str1 = "Hello";
    
    // We can also use constructor initialization
    string str2(" World!");

    // The below initialiation creates a string with 5 'A's
    string str3(5,'A');

    cout << "String 1 = " << str1 << "\n";
    cout << "String 2 =" << str2 << "\n";
    cout << "String 3 = " << str3 << endl;

    // Concatenation - Use + operator
    string str4 = str1+str2;
    cout << "Greeting: " << str4 << endl;

    // String length/size
    int str1_len = str1.length();
    int str2_len = str2.size();
    cout << "Length of str1 and str2 is " << str1_len << " and " << str2_len << endl;

    // Is empty check
    string str5 = "";
    if(str5.empty()){
        cout << "String 5 is empty" << endl;
    }
    else{
        cout << "String 5 is not empty" << endl;
    }

    // Accessing Characters
    // You can access characters using [] (no bounds checking) or .at() (safe, throws error if out of bounds)
    string word = "Verify";
    cout << "First char: " << word[0] << endl;
    cout << "Second char: " << word.at(1) << endl;
    
    // Modifying a specific character
    word[0] = 'v'; 
    cout << "Modified word: " << word << endl; // prints "verify"
    
    // Substrings & Searching
    string sentence = "SystemVerilog and C++ are used in DV";
    
    // Use .substr(start_index, length) to extract a portion of the string
    string sub = sentence.substr(18, 3); // Extracts "C++"
    cout << "Substring: " << sub << endl;

    // Use .find(substring) to search for a string. Returns the index or string::npos if not found
    size_t position = sentence.find("C++");
    if (position != string::npos) {
        cout << "'C++' found at index: " << position << endl;
    }

    return 0;
}
