/*** 4-Bit Synchronous Up Counter ***/

#include "systemc.h"
#include <iostream>
#include <bitset>

using namespace std;
/* DESIGN */
SC_MODULE(counter) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> enable;
    sc_out<sc_uint<4>> count;

    private:
        sc_uint<4> count_reg{0};

    void counter_process() {
        if (rst.read()) {
            count_reg = 0;
        } else if (enable.read()) {
            count_reg = count_reg + 1; // sc_uint<4> naturally wraps 15 -> 0
            }
        count.write(count_reg);
    }

    public:
        SC_CTOR(counter) {
            SC_METHOD(counter_process);
            sensitive << clk.pos();
        }
    };

/* TESTBENCH */
SC_MODULE(test) {
    sc_in<bool> clk;
    sc_out<bool> rst;
    sc_out<bool> enable;
    sc_in<sc_uint<4>> count;

    void stimulus() {
        // Reset state
        rst.write(true);
        enable.write(false);
        wait(clk.posedge_event());

        // De-assert reset for 2 cycles
        wait(clk.posedge_event());
        rst.write(false);
        enable.write(true);

        // Run for 20 clock cycles to observe wrap-around (0 to 15 to 0)
        for (int i = 0; i < 20; ++i) {
            wait(clk.posedge_event());
        }

        // Test synchronous reset while enabled
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
             << " ENABLE = " << enable.read()
            //  << " COUNT = " << bitset<4>(count.read())
            << " COUNT = " << count.read()
             << endl;
    }

    SC_CTOR(test) {
        SC_THREAD(stimulus);
        sensitive << clk;

        // Sample on negative clock edge to avoid race conditions with posedge updates
        SC_METHOD(monitor);
        sensitive << clk.neg();
        dont_initialize();
    }
};

/* MAIN METHOD */
int sc_main(int argc, char* argv[]){

    sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true);
    sc_signal<bool> rst;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4>> count;

    counter dut("dut");
    test tb("tb");

    dut.clk(clk);
    dut.rst(rst);
    dut.enable(enable);
    dut.count(count);

    tb.clk(clk);
    tb.rst(rst);
    tb.enable(enable);
    tb.count(count);

    sc_trace_file* tf = sc_create_vcd_trace_file("waves/sync_counter");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "clk");
    sc_trace(tf, rst, "rst");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, count, "count");

    sc_start();

    sc_close_vcd_trace_file(tf);

    return 0;
}