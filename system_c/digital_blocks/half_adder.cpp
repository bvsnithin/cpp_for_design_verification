#include <systemc.h>
SC_MODULE(half_adder){
  sc_in<bool> a;
  sc_in<bool> b;
  sc_out<bool> sum;
  sc_out<bool> carry;
  
  void process(){
    sum.write(a.read() ^ b.read());
    carry.write(a.read() && b.read());
  }
  
  SC_CTOR(half_adder){
    SC_METHOD(process);
    sensitive << a << b;
  }
};


SC_MODULE(tb){
  sc_out<bool> a;
  sc_out<bool> b;
  sc_in<bool> sum;
  sc_in<bool> carry;
  
  void test(){
	  a.write(false); 
    b.write(false); 
    wait(10, SC_NS);
    
    a.write(false); 
    b.write(true); 
    wait(10, SC_NS);
    
    a.write(true); 
    b.write(false); 
    wait(10, SC_NS);
    
    a.write(true); 
    b.write(true); 
    wait(10, SC_NS);
    
    sc_stop();
  }
  
  SC_CTOR(tb){
  	SC_THREAD(test);
  }
};

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> sig_a, sig_b, sig_sum, sig_cout;

    half_adder dut("DUT");
    dut(sig_a, sig_b, sig_sum, sig_cout);

    tb testbench("TB");
    testbench(sig_a, sig_b, sig_sum, sig_cout);

    sc_trace_file *tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, sig_a, "a");
    sc_trace(tf, sig_b, "b");
    sc_trace(tf, sig_sum, "sum");
    sc_trace(tf, sig_cout, "cout");

    sc_start();

    sc_close_vcd_trace_file(tf);
    return 0;
}
