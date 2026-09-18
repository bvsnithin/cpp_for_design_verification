#include "systemc.h"

// In this example we will see how updating a signal schedules a sensitive process that is listening on that signal 
// Here the monitor process is sensitive(listening) on the data. It is triggered on changes to data
SC_MODULE (signal_wakeup_process){
    sc_signal<int> data{"data"};

    SC_CTOR(signal_wakeup_process){
        SC_THREAD(driver);
        SC_METHOD(monitor);
        sensitive << data;
        dont_initialize();
    }

    void driver(){
        cout << "Initial value of data = " << data.read() 
             << " Delta Count = " << sc_delta_count() 
             << " Time = " << sc_time_stamp() << endl;
        
        data.write(42);

        cout << "Driver reads data = " << data.read() 
             << " Delta Count = " << sc_delta_count() 
             << " Time = " << sc_time_stamp() << endl;
        
        wait(SC_ZERO_TIME);

        data.write(62);

        cout << "Driver reads data = " << data.read() 
             << " Delta Count = " << sc_delta_count()
             << " Time = " << sc_time_stamp() << endl; // Reads 42 only because data is not yet updated to 62
        
        wait(SC_ZERO_TIME);

        cout << "Driver reads data = " << data.read() 
             << " Delta Count = " << sc_delta_count()
             << " Time = " << sc_time_stamp() << endl;
        
    }

    void monitor(){
        cout << "::::  Monitor triggered because 'data' is updated! ::::" 
             << " Time = " << sc_time_stamp() << endl;

        cout << "Monitor reads data = " << data.read()
             << " Delta Count = " << sc_delta_count()
             << " Time = " << sc_time_stamp() << endl;
    }
};

int sc_main(int argc, char* argv[]){
    signal_wakeup_process top("top");
    sc_start();
    return 0;
}

/* OUTPUT STATEMENTS */
/*
Initial value of data = 0 Delta Count = 1 Time = 0 s
Driver reads data = 0 Delta Count = 1 Time = 0 s
::::  Monitor triggered because 'data' is updated! :::: Time = 0 s
Monitor reads data = 42 Delta Count = 2 Time = 0 s
Driver reads data = 42 Delta Count = 2 Time = 0 s
::::  Monitor triggered because 'data' is updated! :::: Time = 0 s
Monitor reads data = 62 Delta Count = 3 Time = 0 s
Driver reads data = 62 Delta Count = 3 Time = 0 s
*/