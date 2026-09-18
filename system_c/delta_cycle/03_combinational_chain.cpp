#include "systemc.h"

SC_MODULE(combinational_chain){
    sc_signal<int> a{"a"}, b{"b"}, c{"c"};

    SC_CTOR(combinational_chain){
        SC_THREAD(driver);

        SC_METHOD(calculate_b); 
        sensitive << a; 
        dont_initialize();

        SC_METHOD(calculate_c); 
        sensitive << b; 
        dont_initialize();

        SC_METHOD(monitor_c); 
        sensitive << c; 
        dont_initialize();
    }

    void driver(){
        cout << "Initial value of a = " << a.read() 
             << " Delta Count = " << sc_delta_count() 
             << " Time = " << sc_time_stamp() << endl;
        
        wait(10, SC_NS);

        cout << "Value of a = " << a.read() 
             << " Delta Count = " << sc_delta_count() 
             << " Time = " << sc_time_stamp() << endl;

        a.write(5);

        cout << "Value of a = " << a.read() 
             << " Delta Count = " << sc_delta_count() 
             << " Time = " << sc_time_stamp() << endl;
    }

    void calculate_b() {
        cout << "B process: a=" << a.read() << " time=" << sc_time_stamp()
                  << " delta=" << sc_delta_count() << endl;
        b.write(a.read() * 2);
    }
    void calculate_c() {
        cout << "C process: b=" << b.read() << " time=" << sc_time_stamp()
                  << " delta=" << sc_delta_count() << endl;
        c.write(b.read() + 1);
    }
    void monitor_c() {
        cout << "Final c=" << c.read() << " time=" << sc_time_stamp()
                  << " delta=" << sc_delta_count() << endl;
    }
};

int sc_main(int argc, char* argv[]){
    combinational_chain top("top");
    sc_start();
    return 0;
}

/* OUTPUT STATEMENTS */
/*
Initial value of a = 0 Delta Count = 1 Time = 0 s
Value of a = 0 Delta Count = 3 Time = 10 ns
Value of a = 0 Delta Count = 3 Time = 10 ns
B process: a=5 time=10 ns delta=4
C process: b=10 time=10 ns delta=5
Final c=11 time=10 ns delta=6
*/

/*
Question:  Why is delta count = 3 after 10NS wait?
- Because, Advancing time consumes delta cycle. Initially delta count was 1 after the simulation has started. 
- During the advancement of time from 0ns to 10ns, delta count changed to 2
- After 10ns, the delta count became 3

Explanation of chaining
- a gets written.
- Kernel applies it. Now a is officially updated.
- calculate_b is watching a, so it wakes up. New delta cycle.
- calculate_b writes b.
- Kernel applies it. b is now updated.
- calculate_c is watching b, so it wakes up. New delta cycle.
- calculate_c writes c.
- Kernel applies it.
- monitor_c is watching c, so it wakes up. New delta cycle.

All of this happens at the same time step, 10ns!!!!!
*/