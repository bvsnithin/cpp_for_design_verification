#include "systemc.h"

// In this example, we will see how sc_signal writes are deferred.
// A write() requests a new value. The current value changes during the update phase.
// The update phase happens after the running process suspends or returns
SC_MODULE(deferred_signal_update){
    sc_signal<int> value {"value"};

    void run(){
        cout << "[TIME = " << sc_time_stamp() << "]" 
             << " Before write: value = " << value.read()
             << " [DELTA = " << sc_delta_count() << "] "<< endl;    // Prints delta = 1
        
        value.write(10);

        cout << "Immediately after write: value = " << value.read()
             << " [DELTA = " << sc_delta_count() << "] "<< endl;   // Prints delta = 1 

        wait(SC_ZERO_TIME);

        cout << "[TIME = " << sc_time_stamp() << "] " 
             << "After write: value = " << value.read()
             << "[DELTA = " << sc_delta_count() << "] " << endl;    // Prints delta = 2. Why? Because SC_ZERO_TIME advances delta count by 1!

        wait(10, SC_NS);

        cout << "[TIME = " << sc_time_stamp() << "] " 
             << "After write: value = " << value.read()
             << "[DELTA = " << sc_delta_count() << "] " << endl;    // Prints delta = 4. Why? Because any advancement in time increments delta by 2

        wait(10, SC_NS);

        cout << "[TIME = " << sc_time_stamp() << "] " 
             << "After write: value = " << value.read()
             << "[DELTA = " << sc_delta_count() << "] " << endl;    // Prints delta = 6. Why? Because any advancement in time increments delta by 2

        wait(SC_ZERO_TIME);

        cout << "[TIME = " << sc_time_stamp() << "] " 
             << "After write: value = " << value.read()
             << "[DELTA = " << sc_delta_count() << "] " << endl;    // Prints delta = 7. Why? Because SC_ZERO_TIME advances delta count by 1!
    }

    SC_CTOR(deferred_signal_update){
        SC_THREAD(run);
    }
};

int sc_main(int argc, char* argv[]) {
    deferred_signal_update top("top");
    sc_start();
    return 0;
}

/*PRINT STATEMENTS

[TIME = 0 s] Before write: value = 0 [DELTA = 1]
Immediately after write: value = 0 [DELTA = 1]
[TIME = 0 s] After write: value = 10[DELTA = 2]

:::: NOTES ::::
1. EVALUATION PHASE : Code runs. write(X) queues 'X' (read() returns old value).
2. UPDATE PHASE     : Kernel applies queued signal updates.
3. DELTA CYCLE      : Zero-time step. Starts at DELTA = 1 when simulation runs.
4. wait(SC_ZERO_TIME): Triggers Update Phase -> Increments DELTA -> Signal updates.
5. TIME ADVANCE     : Time stamp ONLY increases with wait(N, SC_NS/SC_PS/etc).
*/