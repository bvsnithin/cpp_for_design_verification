/* 
Multiplexer Design: 4x1 MUX

4 input lines
2 select lines
1 output line

*/ 

#include "systemc.h"
#include <bitset>
using namespace std;

SC_MODULE(MUX4X1){
  // Declare Ports
  sc_in<sc_uint<4>> in;   // 4 input lines
  sc_in<sc_uint<2>> sel;  // 2 select lines
  
  sc_out<bool> out;
  
  // Combinational Logic
  void process_mux(){
    // Using switch case 
    switch(sel.read()){
      case 0:
        out.write(in.read()[0]);
        break;
      case 1:
        out.write(in.read()[1]);
        break;
      case 2:
        out.write(in.read()[2]);
        break;
      case 3:
        out.write(in.read()[3]);
        break;
    }
  }
  
  SC_CTOR(MUX4X1){
    SC_METHOD(process_mux);
    sensitive << in << sel;
  }
};


// Testbench
SC_MODULE(test){
    sc_out<sc_uint<4>> in;
    sc_out<sc_uint<2>> sel;
  
    sc_in<bool> out;
  
  void stimulus(){
    cout << " TIME  | MUX INPUTS (3210) | SEL | OUTPUT " << endl;
    
    in.write("1010");
    
    for(int i = 0;i<4;i++){
      sel.write(i);
      wait(10,SC_NS);
      
      cout << " " << sc_time_stamp() << " |        "  << bitset<4>(in.read()) << "        |  " << i << "  |   " << out.read() << endl;
    }
    
    in.write("0101");
    
    for(int i = 0;i<4;i++){
      sel.write(i);
      wait(10,SC_NS);
      
      cout << " " << sc_time_stamp() << " |        "  << bitset<4>(in.read()) << "        |  " << i << "  |   " << out.read() << endl;
    }
    
    sc_stop();
  }
  
  SC_CTOR(test){
    SC_THREAD(stimulus);
  }
};

int sc_main(int argc, char* argv[]){
  // Declare signals
  sc_signal<sc_uint<4>> sig_mux_in;
  sc_signal<sc_uint<2>> sig_sel;
  
  sc_signal<bool> sig_mux_out;

  // Instantiate Modules
  MUX4X1 mux("Mux_DUT");  // Device Under Test
  test tb("Mux_TB");    // Testbench

  // Port Binding
  // Connect Mux DUT
  mux.in(sig_mux_in);
  mux.sel(sig_sel);
  mux.out(sig_mux_out);

  // Connect Testbench Stimulus
  tb.in(sig_mux_in);
  tb.sel(sig_sel);
  tb.out(sig_mux_out);
  
  sc_start();
  
  return 0;
}