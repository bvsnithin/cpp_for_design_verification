#include <iostream>

int main()
{
    std::cout << "Hello World\n";
    return 0;
}

/*

Let's dissect the code line by line

1) #include <iostream>
#: This signals a preprocessor directive. 
- It basically indicates that what follows after this `#` is going to be a preprocessor directive.

- A preprocessor runs before the actual compilation stage. 
- A directive is something that preprocessor runs before the compiler translates the code into machine instructions.

- A preprocessor modifies your source code text before compilation, 
- and a directive is a special command that tells the preprocessor what text changes to make.

include: This is the preprocessor directive! 
- The directive `include` tells the preprocessor to copy and paste the contents of another file(include the content) into our script `hello_world.cpp`.

<iostream>: This is the standard input and output stream standard library file. 

std::cout
std::cin
std::cerr

To put into final words:
#include <iostream> means -> Hey preprocessor, could you please include the iostream here!?


2) int main()

- Every executable cpp code needs this main function!
- But why? A cpp executable needs a starting point and main() is the starting point! 
- After we compile the program we get an executable program. 
- When we execute this executable file, the program needs to know where to start execuation from. Hence to determine the starting point we need a main function in the cpp code
- It is just the starting point of execution/where execution begins
- `int` here indicates the return type of the function

3) std::cout << "Hello World\n";

- std stands for standard
- cpp's standard library has things such as cout, cin, string, vector etc.
- std is the namespace and the things like cout, cin etc are organized inside the namespace std. 
- `::` is the scope resoluation operator
- `std::cout` basically means - look inside the std namespace and use cout
- `<<`  is an operator used to send the data to cout
- To avoid using std everytime, we can skip that with `using namespace std`
- Then simple cout << "Hello World\n" will work fine. 

*/