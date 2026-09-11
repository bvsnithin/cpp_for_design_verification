#include <iostream>
#include <cstdlib>  // required for malloc, calloc, realloc, free
using namespace std;

int main(){
    int x = 10;     // x is an int variable that stores the value 10
    int* px = &x;   // px is an int pointer variable that stores the address of variable x
    // cpp also allows to declare variables of int**(pointer to a pointer variable) and int*** as well
    // Does it mean we can create a variable of type int*******? Yes, it's valid but never used beyond int**


    cout << "Value of x is: " << x << endl;     // Prints 10
    cout << "Value(stores address of variable x) of px is: " << px << endl;   // Prints address of x

    // Example output
    // Value of x is: 10
    // Value(stores address of variable x) of px is: 0x7ffe340a2894

    // Here x(storing a value of 10), is present in stack
    // Similarly, even px is on stack
    
    // To allocate memory in heap -> we need to create variables using the "new" keyword
    int* pnewx = new int(100); // new returns an address! Important to remember. 
    // In cpp, new always returns an address and hence the type on the lhs should be a pointer! 
    // "new int(100)" allocates space in heap for a value of "100"
    // However, pnewx is still in stack. 

    cout << "\nAddress where 100 is present: " << pnewx << endl;
    cout << "Address where pnewx is present: " << &pnewx << endl;

    // Address where 100 is present: 0x12d92c0
    // Address where pnewx is present: 0x7ffe340a2888

    // Compared to previous results, we can see that heap memory has a whole different memory address pattern

    // ::::::: DYNAMIC MEMORY ALLOCATION WITH MALLOC AND CALLOC :::::::
    // The concepts of malloc and calloc are from C language. In cpp, new is used for dynamic memory allocation.
    // DMA allows programs to request memory during runtime

    // Compile time memory allocation example: A fixed/static array is an example for this
    int arr[3] = {1,2,3};
    cout << "\nStatic arr: " << arr[0]<< " " << arr[1]<<" " << arr[2] <<"\n";
    cout << "Addresses of arr elements: " << &arr[0] << " " << &arr[1] << " " << &arr[2] <<"\n";

    //Dynamic array - Uses new keyword to allocate memory in the heap. Static allocates memory in the stack. 
    int size;
    cout<<"\nEnter the size for the dynamic array: \n";
    cin>>size;

    // Since we can change the value of size during the runtime, it's called dynamic array. 

    // new returns an address, so we need int* for the pointer type

    int* arrPtr = new int[size]();
    for(int i = 0;i<size;i++){
        cout << "Value at address: "<<arrPtr+i<<"is: "<<arrPtr[i]<<"\n";
    }

    // Malloc vs New
    // New is type safe as it returns the exact pointer type like int* or char* but Malloc returns the generic void* pointer which needs to be cast manually. 
    // When we use "new" with parantheses like new int[size]() would initialize the values to 0 for int but malloc does not do that.

    // Failure Behavior: 
    //   - malloc/calloc return NULL if memory allocation fails. You must always check for NULL before dereferencing.
    //   - new throws std::bad_alloc exception by default. Use new(std::nothrow) if you want it to return nullptr instead.

    //malloc example
    cout<<"\n:::::: Malloc ::::::\n";
    int* arrPtr_m = (int*)malloc(5*sizeof(int));
    for(int i =0;i<5;i++){
        cout << "Value at address: "<<arrPtr_m+i<<"is: "<<arrPtr_m[i]<<"\n";
    }

    // calloc (contiguous allocation) differs from malloc in two key ways: it takes two distinct arguments (element count and element size) 
    // and automatically zero-initializes all allocated bytes.

    cout << "\n :::::: Calloc :::::: \n";
    int* arrptr_c = (int*)calloc(5, sizeof(int));
    for(int i = 0;i<5;i++){
        cout << "Value at address: "<<arrptr_c+i<<"is: "<<arrptr_c[i]<<"\n";
    }

    // Deallocation rules (IMPORTANT - mismatching these is Undefined Behavior)::
    //   - malloc/calloc/realloc  ->  use free(ptr)
    //   - new                    ->  use delete ptr
    //   - new[]                  ->  use delete[] ptr   (array form!)
    // Never mix them (e.g. free() on a new'd pointer, or delete on a malloc'd pointer)

    // Freeing malloc/calloc allocated memory
    free(arrPtr_m);
    free(arrptr_c);

    // Let's delete pnewx (heap) and then try to dereference it
    delete pnewx;
    // WARNING: *pnewx below is UNDEFINED BEHAVIOR (UB), not just a garbage value.
    // The memory has been returned to the OS/allocator. Dereferencing it may crash, corrupt data,
    // or appear to work (dangerously). Always set pointer to nullptr after delete: pnewx = nullptr;
    // cout << "Value after deletion: " << *pnewx << endl; // DO NOT DO THIS - UB!

    // WARNING: delete px is UNDEFINED BEHAVIOR - px points to stack memory (variable x), not heap.
    // You can ONLY call delete on memory that was allocated with new.
    // Doing this will almost certainly crash the program (segfault or heap corruption).
    // delete px;  // DO NOT DO THIS - UB!

    // ::::::: REALLOC :::::::
    // realloc (re-allocation) is a C function (from <cstdlib>) used to RESIZE previously malloc/calloc allocated memory.
    // Syntax: void* realloc(void* ptr, size_t new_size);
    // It takes the original pointer and a NEW total size (in bytes), not the delta.

    // Q: Can we INCREASE memory through realloc?
    // A: YES. realloc will try to expand the block in-place if there is free contiguous memory right after it.
    //    If not, it will: allocate a brand new block of new_size, copy the old data into it, free the old block,
    //    and return the new pointer. The OLD pointer should NOT be used after realloc.

    // Q: What happens when we SHRINK with realloc?
    // A: The block is trimmed. The data up to the new size is preserved, and the excess memory is released.
    //    The pointer value MAY or MAY NOT change (implementation defined), but it's safe to use the returned pointer.
    //    The truncated data beyond new_size is simply gone.

    // realloc example: start with 3 ints, grow to 6, then shrink to 2
    int* rptr = (int*)malloc(3 * sizeof(int));
    if(rptr == nullptr) return 1; // always check malloc result
    rptr[0] = 10; rptr[1] = 20; rptr[2] = 30;

    // Growing: resize from 3 to 6 ints
    // IMPORTANT: always assign realloc to a TEMP pointer first.
    // If realloc fails it returns NULL, and assigning directly to rptr would leak the original block.
    int* temp = (int*)realloc(rptr, 6 * sizeof(int));
    if(temp == nullptr){ free(rptr); return 1; } // realloc failed, original block still valid
    rptr = temp; // safe to update now
    // rptr[3], rptr[4], rptr[5] are uninitialized (realloc does NOT zero-initialize new bytes unlike calloc)
    rptr[3] = 40; rptr[4] = 50; rptr[5] = 60;
    cout << "\n:::::: Realloc (grown to 6) ::::::";
    for(int i = 0; i < 6; i++) cout << " " << rptr[i];
    cout << "\n";

    // Shrinking: resize from 6 to 2 ints
    temp = (int*)realloc(rptr, 2 * sizeof(int));
    if(temp == nullptr){ free(rptr); return 1; }
    rptr = temp;
    // Values 30,40,50,60 are gone. Only rptr[0]=10 and rptr[1]=20 remain.
    cout << "After shrink to 2: " << rptr[0] << " " << rptr[1] << "\n";

    free(rptr); // must free when done - realloc'd memory is freed with free()

    // Note: realloc does NOT exist for new/delete in C++. Use std::vector instead, 
    // which handles dynamic resizing automatically and safely.



    return 0;
}