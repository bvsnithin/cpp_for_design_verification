// Modules are basically the building blocks of SystemC
// A module is a container that contain data members, processes, instance of other modules and ports for communication. 

// Modules can be created in 2 ways
// 1) By extending the sc_module class
// 2) Using the SC_MODULE macro

// :::::::::: USING sc_module CLASS ::::::::::
/*
class module_name : public sc_module{

};
*/

// :::::::::: USING SC_MODULE MACRO ::::::::::
/*
SC_MODULE (module_name){

};
*/

// Comparison of SystemVerilog and SystemC
/*
SystemVerilog
1) Module               -> module my_mod(.....);
2) Combinational Block  -> always_comb
3) Sequential Block     -> always_ff @(posedge clk)
4) Initial Block        -> initial
5) Variable/Nets        -> logic, wire, reg
6) Ports                -> input, output, inout

SystemC
1) Module               -> SC_MODULE (my_mod) {};
2) Combinational Block  -> SC_METHOD(proc); sensitivity << signals;
3) Sequential Block     -> SC_METHOD(proc); sensitivity << clk.pos();
4) Initial Block        -> SC_THREAD(proc);
5) Variable/Nets        -> sc_signal<T>, sc_uint<W>, sc_logic
6) Ports                -> sc_in<T>, sc_out<T>, sc_inout<T>
*/

// Below is an example code for a Hardware Module -> AND gate and a testbench for it
/*
module and_gate(
    input a,
    input b, 
    output out
);
    assign out = a&b;
endmodule

// Testbench:
module and_test;
    logic a;
    logic b;
    logic out;

    and_gate (.*);

    initial begin
        $dumpfile("waves/and_gate.vcd");
        $dumpvars(1, and_test);
    end

    initial begin
        repeat(10) begin
            a = $urandom_range(0,1);
            b = $urandom_range(0,1);
            #1;
            $display("a = %0b, b = %0b, out = %0b", a,b,out);
            #1;
        end
        $finish;
    end
endmodule

Below is the SystemC code for AND gate
*/

#include "systemc.h"
#include <iostream>
#include <cstdlib> // For rand()

// AND Gate hardware module declaration using the SC_MODULE macro
SC_MODULE(and_gate) {
  
  // Port declarations
  sc_in<bool> a;
  sc_in<bool> b;
  sc_out<bool> out;
  
  // Combinational function modeling for the AND operation
  void do_and(){
    
  	// For assignment we have to use the write() operation
    // read() fetches the current port values
    // write() updates the output port
    
    out.write(a.read() && b.read()); // out = a && b;
    
  }
  
  // Constructor -> Here we initialize the module name
  SC_CTOR(and_gate){
  	
    // SC_METHOD is similar to always_comb
    SC_METHOD(do_and);
 	// This is the sensitivity list. do_and is triggered whenever port 'a' or 'b' changes values
    sensitive << a << b; 
    
  }
    
};

SC_MODULE(and_test){
  sc_signal<bool> a;
  sc_signal<bool> b;
  sc_signal<bool> out;
  
  and_gate *dut; // Pointer to instantiate the DUT! 
  
  // This is a testbench process thread to drive the stimulus
  void test_process(){
  	
    // Loop 10 times 
    for(int i = 0;i<10;i++){
      bool rand_a = rand()%2;
      bool rand_b = rand()%2;
      
      a.write(rand_a);
      b.write(rand_b);
      
      wait(1, SC_NS); // #1ns delay
      
      std::cout << "a = " << a.read() << " b = " << b.read() << " out = " << out.read() << std::endl;
      
      wait(1, SC_NS);
    }
    
    sc_stop(); // End of simulation
  }
  
  // Testbench constructor
  SC_CTOR(and_test){
    dut = new and_gate("dut"); //Instantiate the AND gate
    
    // Bind testbench signals to the DUT ports
    dut->a(a);
    dut->b(b);
    dut->out(out);
    
    // SC_THREAD allows execution over time
    SC_THREAD(test_process);
  }
  
  // Destructor to clean up the memory allocated in the heap for the DUT
  ~and_test() {
    delete dut;
  }
  
};

// Top level - entry point for the SytemC kernel! Execution starts from here
int sc_main(int argc, char* argv[]){
  
  // Instantiate the testbench
  and_test tb("tb");
  
  // Start SystemC simulation
  sc_start();
  
  return 0;
}


// Quick primer on object creation in SystemC
//   C++ pointer variable name
//   |   
//   v          Creates on Heap
//              v
//  dut     =  new  and_gate("dut");
//                   ^        ^
//                   |        Name given to the SystemC simulator kernel
//                   SystemC Module Class

// Any object created with the new keyword is allocated memory in the heap


/* HEAP ALLOCATION
1. Declare pointer (holds address)
and_gate *dut; 

2. Allocate on HEAP. 'new' returns address (e.g. 0x00FF). This address is stored in dut pointer created above
dut = new and_gate("dut"); 

3. Must manually free when done
delete dut;
*/

/* STACK ALLOCATION
Heap  -> Unmanaged memory and hence needs to be cleared
Stack -> Stack is automatically managed by C++

- It is destroyed automatically as soon as execution leaves the function or block {} where it was created

- We don't need to use the "new" keyword here for stack allocations

Syntax: and_test tb("tb);
*/

/*
1. STACK OBJECT VARIABLE (No '*' in declaration or no "new" keyword)
- 'tb_obj' stores the ENTIRE object directly on the stack

Syntax: and_test tb_obj("tb"); 

Accessing Signals
- tb_obj.a.write(1);
- bool val = tb_obj.out.read();
- For stack object variables use the "." operator

2. HEAP POINTER VARIABLE (Requires '*' and the new keyword)
- 'tb_ptr' is a pointer variable storing an ADDRESS to an object on the heap

Syntax: and_test *tb_ptr = new and_test("tb");

Access signals using '->'
tb_ptr->a.write(1);          
bool val = tb_ptr->out.read(); 
*/
