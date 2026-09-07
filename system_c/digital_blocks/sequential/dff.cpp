/* DFF: D Flip Flop */

#include "systemc.h"

using namespace std;

/***** DESIGN *****/
SC_MODULE(dff) {
  sc_in<bool> clk;
  sc_in<bool> rst_n; // Asynchronous Reset
  sc_in<bool> d;
  sc_out<bool> q;

  void ff_process() {
    if (!rst_n.read()) {
      q.write(false);
    } else {
      q.write(d.read());
    }
  }

  SC_CTOR(dff) {
    SC_METHOD(ff_process);
    sensitive << clk.pos() << rst_n.neg();
  }
};

/***** TESTBENCH *****/
SC_MODULE(test) {

  sc_in<bool> clk; // Since we have sc_clock driving it in the main function, we have clk as sc_in<bool>
  sc_out<bool> rst_n;
  sc_out<bool> d;

  sc_in<bool> q;

  void stimulus() {
    // Initial State
    rst_n.write(true);
    d.write(false);
    wait(2, SC_NS);

    // Apply Asynchronous Reset
    cout << "@" << sc_time_stamp() << " Asserting Reset" << endl;
    rst_n.write(false);
    wait(12, SC_NS);

    // Deassert Reset
    cout << "@" << sc_time_stamp() << " Deasserting Reset" << endl;
    rst_n.write(true);
    wait(8, SC_NS);

    // Apply D = 1
    cout << "@" << sc_time_stamp() << " Driving D = 1" << endl;
    d.write(true);
    wait(10, SC_NS);

    // Apply D = 0
    cout << "@" << sc_time_stamp() << " Driving D = 0" << endl;
    d.write(false);
    wait(10, SC_NS);

    // Apply Async Reset while D = 1
    d.write(true);
    wait(3, SC_NS);
    cout << "@" << sc_time_stamp() << " Asserting Async Reset mid-clock" << endl;
    rst_n.write(false);
    wait(7, SC_NS);

    rst_n.write(true);
    wait(10, SC_NS);

    // End Simulation
    cout << "@" << sc_time_stamp() << " Simulation Finished" << endl;
    sc_stop();
  }

  // Monitor Process
  void monitor() {
    cout << "@" << sc_time_stamp() 
         << " | CLK=" << clk.read() 
         << " | RST_N=" << rst_n.read() 
         << " | D=" << d.read() 
         << " | Q=" << q.read() << endl;
  }

  SC_CTOR(test) {
    SC_THREAD(stimulus);

    SC_METHOD(monitor);
    sensitive << clk << rst_n << d << q;
  }
};

/***** MAIN FUNCTION *****/
int sc_main(int argc, char *argv[]) {

  // Signal Declarations
  
  // Instantiate sc_clock: 
  // Name, Period (10ns), Duty Cycle (0.5 default), Start Time (0ns default), First edge (true = posedge)
  sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true);
  sc_signal<bool> rst_n;
  sc_signal<bool> d;
  sc_signal<bool> q;

  dff dut("dut");
  test tb("tb");

  // DUT CONNECTION
  dut.clk(clk);
  dut.rst_n(rst_n);
  dut.d(d);
  dut.q(q);

  // TESTBENCH CONNECTION
  tb.clk(clk);
  tb.rst_n(rst_n);
  tb.d(d);
  tb.q(q);

  // WAVEFORM SETUP
  sc_trace_file *tf = sc_create_vcd_trace_file("waves/dff_waveform");
  tf->set_time_unit(1, SC_NS);
  sc_trace(tf, clk, "clk");
  sc_trace(tf, rst_n, "rst_n");
  sc_trace(tf, d, "d");
  sc_trace(tf, q, "q");

  sc_start();

  sc_close_vcd_trace_file(tf);

  return 0;
}