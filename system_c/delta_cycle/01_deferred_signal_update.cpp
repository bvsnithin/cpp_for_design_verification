#include "systemc.h"

// In this example, we will see how sc_signal writes are deferred.
// A write() requests a new value. The current value changes during the update phase.
// The update phase happens after the running phase is completed
SC_MODULE(deferred_signal_update){
    sc_signal<int> value {"value"};

    void run(){
        cout << "[TIME = " << sc_time_stamp() << "]" 
             << " Before write: value = " << value.read()
             << " [DELTA = " << sc_delta_count() << "] "<< endl;
        
        value.write(10);

        cout << "Immediately after write: value = " << value.read()
             << " [DELTA = " << sc_delta_count() << "] "<< endl;
        wait(SC_ZERO_TIME);

        cout << "[TIME = " << sc_time_stamp() << "] " 
             << "After write: value = " << value.read()
             << "[DELTA = " << sc_delta_count() << "] " << endl;
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

*/