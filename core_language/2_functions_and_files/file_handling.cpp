/* 
:::::::::::::: FILE HANDLING ::::::::::::::
In C++, file handling is managed through the <fstream> library using 3 core classes:

1) ofstream (Output File Stream)      -> Writes to files
2) ifstream (Input File Stream)       -> Reads from files
3) fstream  (Input/Output File Stream)-> Reads and writes to files
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    string filename = "dummy.txt";

    // ::::::::: WRITING TO A FILE (ofstream) :::::::::
    ofstream outFile(filename); // Create an instance of ofstream

    if (outFile.is_open()) {
        outFile << "Hello World!" << endl;
        outFile << "C++ File Handling Example." << endl;
        outFile << "Line 3." << endl;
        outFile.close(); // Explicitly close to release handle
        cout << "Successfully wrote to " << filename << endl << endl;
    } else {
        cout << "Error: Could not open file for writing." << endl;
    }

    // ::::::::: READING FROM A FILE (ifstream) :::::::::
    ifstream inFile(filename); // Create an instance of ifstream
    string line; // String to store each line inside the file

    if (inFile.is_open()) {
        cout << "Reading contents from " << filename << ":" << endl;

        // Read the file line by line
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
        cout << endl;
        
    } else {
        cout << "Error: Could not open file: " << filename << " for reading." << endl;
    }

    // ::::::::: FILE STATUS CHECKS (fstream) :::::::::
    fstream file(filename, ios::in | ios::out); // Open for both reading and writing

    if (file.good()) {
        cout << filename << " exists and was successfully opened in read/write mode." << endl;
        file.close();
    } else {
        cout << "Error status: File stream state is not good." << endl;
    }

    filename = "numbers.txt";

    // ::::::::: REUSING HANDLES (Read & Append) :::::::::
    
    // 1. Reuse inFile to read the existing numbers first
    // (Note: Do NOT open outFile yet; opening it in default mode will instantly truncate/empty the file!)
    inFile.clear(); 
    inFile.open(filename);

    int num;
    int numbers[100]; // To store the numbers to be appended to the file
    int size = 0;     // Running index

    if (inFile.is_open()) {
        while (inFile >> num) {
            numbers[size] = num * 10;
            size++;
        }
        inFile.close(); 
    } else {
        cout << "Error: Could not open " << filename << " for reading." << endl;
    }

    // 2. Reuse outFile with ios::app mode to append a newline and the new values at the end
    outFile.clear();
    outFile.open(filename, ios::app); // ios::app ensures we append instead of overwriting/truncating. Opening in write mode overwrites!

    if (outFile.is_open()) {
        outFile << "" << endl; // Insert a new line at the end of the existing content
        for (int i = 0; i < size; i++) {
            outFile << numbers[i] << endl;
        }
        outFile.close();
        cout << "Successfully appended multiplied numbers to " << filename << endl;
    } else {
        cout << "Error: Could not open " << filename << " for appending." << endl;
    }

    return 0;
}