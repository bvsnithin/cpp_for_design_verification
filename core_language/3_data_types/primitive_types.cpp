#include <iostream>

int main(){
    // ::::::::::::: PRIMITIVE DATA TYPES :::::::::::::

    // Integer Types - int, short, long
    // Integer data types are "signed" by default
    // Signed - both positive and negative (positive, negative, and zero)
    // Unsigned - only positive (zero and positive)
    int int_val = 20;
    short short_val = 10;
    long long_val = 3000L;
    long long long_long_val = 400LL;

    // int - size = 4 bytes(32 bits)
    // short - size = 2 bytes(16 bits)
    // long - size = 4 bytes or 8 bytes
    // long long - size = 8 bytes

    // unsigned integer - only 0 and positive values
    unsigned int unsigned_int = 500U;

    // Floating Point Data Types - For decimals
    float float_val = 5.34f;
    double double_val = 3434.232;
    long double long_double_val = 1232.34L;

    // Float - Single Precision
    // Double - Double Precision
    // Single precision uses 32 bits and gives about 7 digits of accuracy. 
    // Double precision uses 64 bits and gives about 16 digits of accuracy.

    // Character and Boolean Types
    char letter = 'A';              // Stores a single character, enclosed in single quotes
    bool is_active = true;          // Stores true (1) or false (0)
    
    // sizeof() operator returns the size of a variable or data type in bytes
    std::cout << "Size of char: " << sizeof(letter) << " byte\n";        // 1 byte
    std::cout << "Size of bool: " << sizeof(bool) << " byte\n";          // 1 byte
    std::cout << "Size of int: " << sizeof(int_val) << " bytes\n";       // 4 bytes
    std::cout << "Size of double: " << sizeof(double_val) << " bytes\n"; // 8 bytes

    // ::::::::::::: TYPE CASTING :::::::::::::
    // Casting means converting a value from one type to another. There are two types of casting. Implicit and Explicit
    // Implicit Casting - Automatic conversion by the compiler.
    // When adding int and double, C++ promotes the int to double automatically to avoid losing precision
    int num1 = 10;
    double num2 = 4.5;
    double result = num1 + num2;

    std::cout << "Implicit conversion result: " << result << "\n";

    double n1 = 10.5;
    double n2 = 3.9;
    int sum = n1 + n2; // // Compiler implicitly converts the double result to int, losing the decimal part
    std::cout << "Adding two doubles but storing in int: " << sum << std::endl;

    // Explicit Casting - Manual conversion
    int x = 7;
    int y = 2;
    
    // C-Style Casting - Old way of doing manual conversion in C
    // Syntactically: (target_type)value
    double c_style_div = (double)x / y;
    std::cout << "C-Style Cast result: " << c_style_div << "\n";

    // In cpp there are 4 ways of doing explicit casting

    /*
    1) Static cast - static_cast
    2) Dynamic cast - dynamic_cast
    3) Const cast - const_cast
    4) Reinterpret cast - reinterpret-cast
    */

    // Static Casting - The modern and safe way
    // Syntactically: static_cast<target_type>(value)
    // Preferred because the compiler checks at compile time if the conversion is valid
    double cpp_style_div = static_cast<double>(x) / y;
    std::cout << "Static Cast result: " << cpp_style_div << "\n";

    // Casting double to int truncates the decimal part (loses data)
    double pi = 3.14159;
    int truncated_pi = static_cast<int>(pi);
    std::cout << "Truncated Pi: " << truncated_pi << "\n";

    // Static cast is generally used with primitive data types and compile time known conversions and 
    // Dynamic cast is generally used for runtime checked conversions with inheritance/polymorphic class conversions
    // Const cast and Reinterpret cast are rarely used
    return 0;
}