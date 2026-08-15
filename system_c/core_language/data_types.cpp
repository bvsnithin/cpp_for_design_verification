#include "systemc.h"

// SystemC supports all the Cpp dataypes. In addition to that, it also supports data types for describing hardware. In this file let's look at some of the Cpp datatypes

// Below are the Cpp primitive data types
/*
Integral data types
int				-> 4 bytes maximum or 32 bits size. 2 bytes minimum
signed int     	-> 4 bytes signed representation; both +ve, -ve, and 0. Signed int and int are same.
unsigned int    -> 4 bytes unsigned representation; only 0 and +ve numbers

short			-> 2 bytes or 16 bits
signed short
unsigned short

long			-> 4 bytes minimum or 32 bits
signed long
unsigned long

Decimal data types
float
double
long double

boolean -> bool 1 byte
character -> char 1 byte

SystemC Hardware specific data types are
sc_int
sc_uint
sc_bigint
sc_biguint
sc_logic
sc_bv
sc_lv

*/

int sc_main (int argc, char* argv[]) {
  
  // variable declaration
  int a;
  float b;
  float c;
  
  // initialization
  a = 10;
  b = 20.5;
  
  // addition
  c = a + b;
  
  cout <<"Value of a = "<< c <<endl;
  
  
  // Use sizeof() function to find the size of the variables
  cout << "Size of int a is: " << sizeof(a) << " bytes" << endl;
  
  // Enum - Enumerations
  enum order_status {Pending, Shipped, Delivered};
  
  order_status order1 = Pending;
  
  cout << "Status of order #1: " << order1 << endl;
  
  order1 = Delivered;
  
  cout << "Status of order #1: " << order1 << endl;
  
  // ::::::::: SystemC Data Types :::::::::
  
  // sc_int and sc_uint are fixed width integer data types
  // sc_int<W> Signed: A signed integer template of bit width W
  // sc_uint<W> UnSigned: An unsigned integer tempalte of bit width W
  
  // sc_uint<5>: This is a 5 bit unsigned integer -> 0 to 31
  // sc_int<5>: This is a 5 bit signed integer -> -16(100000 in binary) to 15(01111 in binary)
  
  // These two are capped at 64 bits! Hence they are called as fixed with integer data types
  
  // sc_bigint and sc_biguint are called arbitary width integer types
  // Unlike the sc_int and sc_uint, they are not capped and can take virtually any bit width
  
  sc_int<5> data;
  data = 31;
  cout << data << endl; // This prints -1 because a 5 bit signed data can take a maximum of 15 and not 31
  // Why it prints -1? Because 31 is 11111 in binary and since sc_int is 2's complement format, 
  // 11111 is equal to -16+8+4+2+1 = -1
  
  data = 15;
  cout << data << endl; // This prints 15
  
  sc_uint<5> val; // This is unsigned int so it can be in the range of 0 to 31
  val = 31;
  cout << val << endl; // This prints 31
   
  // sc_logic: It is similar to systemverilog's logic 
  // It is a 4-state wire value
  // 4 states are 0, 1, X, and Z
  // These 4 states can be predefined constants
  // 0 -> SC_LOGIC_0
  // 1 -> SC_LOGIC_1
  // X -> SC_LOGIC_X
  // Z -> SC_LOGIC_Z
  
  sc_logic enable;
  enable = SC_LOGIC_1; // Using predefined constant
  cout << "Value of enable = " << enable << endl;
  
  enable = 0;
  cout << "Value of enable = " << enable << endl;
  
  enable = 'Z';
  cout << "Value of enable = " << enable << endl;
  
  // sc_bv: It is a 2 state bit vector
  // It is an array of W bits
  // Syntax sc_bv<8> data = "10010010"
  // Each bit can be either 0 or 1 and that's why it's called 2 state bit vector
  
  sc_bv<8> register_val;
  register_val = "10010010";
  
  // Accessing and updating
  register_val[0] = '1';
  cout << register_val << endl;
  
  // There is another variant called sc_lv: 4 state logic vector. 
  // Where each bit can be any of 4 states -> 0,1,X,Z
  
  sc_lv<8> logic_val;
  logic_val = "ZZ0010Z1";
  cout << logic_val << endl;
  return 0;
}