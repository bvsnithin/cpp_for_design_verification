/*
LFSR - Linear Feedback Shift Register 
It is a sequential shift register with a combinational logic that causes it to psuedo randomly cycle through sequencec of binary values.
*/

#include "systemc.h"
#include "iostream"
#include <bitset>
// 4 bit LFSR design with a synchronous reset
SC_MODULE(lfsr){
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<sc_uint<4>> out;

    private: sc_uint<4> out_reg;

    void process(){
        if(rst.read()){
            out_reg = 0b0001;
        }
        else{
            bool feedback  = out_reg[3] ^ out_reg[2];
            out_reg = (out_reg << 1) | feedback;
        }
        out.write(out_reg);
    }

    public:
        SC_CTOR(lfsr){
            SC_METHOD(process);
            sensitive << clk.pos();
        }
};

// Testbench
SC_MODULE(test){
    sc_in<bool> clk;
    sc_out<bool> rst;
    sc_in<sc_uint<4>> out;

    void stimulus(){
        rst.write(true);
        
        for(int i =0;i<2;i++){
            wait(clk.posedge_event());
        }

        rst.write(false);

        for (int i = 0; i < 20; ++i) {
            wait(clk.posedge_event());
        }

        rst.write(true);
        for (int i = 0; i < 2; ++i) {
            wait(clk.posedge_event());
        }

        rst.write(false);
        for (int i = 0; i < 5; ++i) {
            wait(clk.posedge_event());
        }

        sc_stop();
    }

    void monitor(){
        cout << "@"
             << sc_time_stamp()
             << " CLK = " << clk.read()
             << " RST = " << rst.read()
            //  << " LFSR = " << out.read().to_string(SC_BIN)
             << " LFSR = " << std::bitset<4>(out.read())
             << " LFSR = " << out.read()
             << endl;
    }

    SC_CTOR(test){
        SC_THREAD(stimulus);
        sensitive << clk;

        // Sample on negative clock edge to avoid race conditions with posedge updates
        SC_METHOD(monitor);
        sensitive << clk.neg();
        dont_initialize();
    }
};

int sc_main(int argc, char* argv[]){

    sc_clock clk("clk",10,SC_NS);
    sc_signal<bool> rst;
    sc_signal<sc_uint<4>> lfsr_out;

    lfsr dut("dut");
    test tb("tb");

    dut.clk(clk);
    dut.rst(rst);
    dut.out(lfsr_out);

    tb.clk(clk);
    tb.rst(rst);
    tb.out(lfsr_out);

    sc_trace_file* tf = sc_create_vcd_trace_file("waves/4bit_lfsr");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");
    sc_trace(tf, rst, "rst");
    sc_trace(tf, lfsr_out, "lfsr_out");
    sc_start();

    sc_close_vcd_trace_file(tf);
    return 0;
}