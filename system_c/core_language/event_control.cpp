// ::::: SYSTEMC EVENT CONTROL :::::

/* An event in SystemC is used for process synchronization. One process can notify an event and another process can wait for that event. 

/ Think of it like:

PROCESS_A                   PROCESS_B
event.notify()  ------->    wait(event) PROCESS_B wakes up

*/

/* ::::::: SC_EVENT :::::::
SystemC provides the sc_event class for this purpose.
Syntax: sc_event event_name;

::::::: IMPORTANT SYSTEMC TERMS :::::::

sc_event -> Used for process synchronizatioN
notify() -> Triggers/schedules an event. There are 3 types of notifications (Immediate, Delayed, Zero-time)
wait() -> Used by SC_THREAD / SC_CTHREAD to wait for an event
next_trigger() -> Used by SC_METHOD for dynamic sensitivity
SC_ZERO_TIME -> Moves execution to a later delta cycle without advancing simulation time

*/


#include "systemc.h"
#include <iostream>

using namespace std;

// ::::::: EVENT DEMO MODULE :::::::
SC_MODULE(event_demo) {

    // :::::::::: EVENT DECLARATIONS ::::::::::
    // sc_event is used for synchronization between processes.

    sc_event data_ready;

    sc_event event1;
    sc_event event2;

    sc_event zero_time_event;

    sc_event timed_event;

    sc_event cancel_event;


    // :::::::: PRODUCER PROCESS ::::::::
    // This process will demonstrate different types of notify().

    void producer() {

        // Start at 0 ns
        cout << "@" << sc_time_stamp() << " Producer started" << endl;

        // :::::::::: IMMEDIATE NOTIFICATION ::::::::::
        // Wait for 10 ns first.
        wait(10, SC_NS);

        cout << "@" << sc_time_stamp() << " Producer: notify(data_ready)" << endl;

        // notify() triggers the event.
        // This is an immediate notification. The notify() has no arguments in it. 
        data_ready.notify();

        // Let's give the consumer a chance to wake up before continuing with the next step.
        wait(10, SC_NS); // 10 nanoseconds delay

        // :::::::::: ZERO TIME NOTIFICATION ::::::::::

        cout << "@" << sc_time_stamp() << " Producer: notify(SC_ZERO_TIME)" << endl;

        // SC_ZERO_TIME means: No simulation time is advanced.
        // But the event is scheduled for a later delta cycle. Find more info on delta cycle and even scheduling at the bottom 
        zero_time_event.notify(SC_ZERO_TIME); // Unlike immediate notification, zero time notification has an argument -> SC_ZERO_TIME

        // Wait so we can clearly see the next example.
        wait(10, SC_NS);

        // :::::::::: DELAYED NOTIFICATION ::::::::::

        cout << "@" << sc_time_stamp() << " Producer: notify(timed_event, 5 ns)" << endl;

        // This event will be triggered 5 ns from now.
        timed_event.notify(5, SC_NS); // The notify function takes an input of delay

        // Wait long enough for timed_event to occur.
        wait(10, SC_NS);

        // :::::::::: EVENT 1 ::::::::::
        cout << "@" << sc_time_stamp() << " Producer: notify(event1)" << endl;
        event1.notify();  // Immediate notification

        wait(10, SC_NS);

        // :::::::::: EVENT 2 ::::::::::
        cout << "@" << sc_time_stamp() << " Producer: notify(event2)" << endl;
        event2.notify();

        wait(10, SC_NS);

        // :::::::::: CANCEL A TIMED EVENT ::::::::::
        cout << "@" << sc_time_stamp() << " Producer: scheduling cancel_event for 20 ns later" << endl;

        cancel_event.notify(20, SC_NS);

        // We only wait for 5 ns.
        wait(5, SC_NS);


        cout << "@" << sc_time_stamp() << " Producer: canceling cancel_event" << endl;

        // cancel() cancels the pending timed notification.
        cancel_event.cancel();

        wait(20, SC_NS);

        cout << "@" << sc_time_stamp()
             << " Producer finished" << endl;
    }


    // :::::::: CONSUMER PROCESS ::::::::

    void consumer() {

        // :::::::::: WAIT FOR EVENT ::::::::::

        cout << "@" << sc_time_stamp() << " Consumer: waiting for data_ready" << endl;

        // wait(event) causes the SC_THREAD to suspend.
        // The thread will continue when data_ready is notified.

        wait(data_ready);

        cout << "@" << sc_time_stamp() << " Consumer: data_ready received" << endl;


        // :::::::::: WAIT FOR ZERO TIME EVENT ::::::::::
        cout << "@" << sc_time_stamp() << " Consumer: waiting for zero_time_event" << endl;

        wait(zero_time_event);

        cout << "@" << sc_time_stamp() << " Consumer: zero_time_event received" << endl;

        // :::::::::: WAIT FOR TIMED EVENT ::::::::::

        cout << "@" << sc_time_stamp() << " Consumer: waiting for timed_event" << endl;

        wait(timed_event);

        cout << "@" << sc_time_stamp() << " Consumer: timed_event received" << endl;
    }


    // :::::::: OR EVENT PROCESS ::::::::

    void or_event_process() {

        cout << "@" << sc_time_stamp() << " OR process: waiting for event1 OR event2" << endl;

        // "|" means OR.
        // The process wakes up when either event1 OR event2 occurs.

        wait(event1 | event2);

        cout << "@" << sc_time_stamp() << " OR process: one of the events occurred" << endl;
    }


    // :::::::: AND EVENT PROCESS ::::::::
    void and_event_process() {

        cout << "@" << sc_time_stamp() << " AND process: waiting for event1 AND event2" << endl;

        // "&" means AND.
        // The process waits until both event1 and event2 have occurred.

        wait(event1 & event2);

        cout << "@" << sc_time_stamp() << " AND process: both events occurred" << endl;
    }


    // :::::::: CANCEL EVENT PROCESS ::::::::
    void cancel_event_process() {

        cout << "@" << sc_time_stamp() << " Cancel process: waiting for cancel_event" << endl;

        // The producer schedules cancel_event for later.
        // But the producer will cancel it before the event occurs.

        wait(cancel_event);

        // If cancel() works correctly, this message should NOT appear.
        cout << "ERROR: cancel_event was received!" << endl;
    }


    // :::::::: SC_METHOD EXAMPLE ::::::::

    // SC_THREAD uses wait().
    // SC_METHOD cannot use wait().

    // For SC_METHOD we can use next_trigger() for dynamic sensitivity.

    void method_process() {

        cout << "@" << sc_time_stamp() << " SC_METHOD executed" << endl;

        // next_trigger() tells the SystemC kernel: "Trigger this method again when data_ready occurs."

        next_trigger(data_ready);
    }

    // :::::::: CONSTRUCTOR :::::::: 

    SC_CTOR(event_demo) {

        // :::::::::: THREAD PROCESSES ::::::::::
        // SC_THREAD can use wait().

        SC_THREAD(producer);
        SC_THREAD(consumer);
        SC_THREAD(or_event_process);
        SC_THREAD(and_event_process);
        SC_THREAD(cancel_event_process);

        // :::::::::: METHOD PROCESS ::::::::::
        SC_METHOD(method_process);

        // We don't want the method to execute automatically at time 0.
        dont_initialize();

        // Initial sensitivity for the method. The method will execute when data_ready is notified.
        sensitive << data_ready;
    }

};

// :::::::::::: MAIN ::::::::::::

// sc_main() is the entry point of a SystemC simulation. Similar idea to main() in a normal C++ program.

int sc_main(int argc, char* argv[]) {

    // Instantiate the module.
    // "demo" is the instance name given to the SystemC kernel.

    event_demo demo("demo");

    // Start SystemC simulation.
    sc_start();

    // Simulation finished.
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Simulation finished at " << sc_time_stamp() << endl;
    cout << "--------------------------------------------------" << endl;
    return 0;
}

// :::::::::::: EVENT CONTROL NOTES ::::::::::::

/*
1) CREATING AN EVENT
sc_event my_event;

2) IMMEDIATE NOTIFICATION
my_event.notify();

This triggers the event at the current simulation time.

IMPORTANT:
- "Immediate" does NOT mean another process immediately starts executing in the middle of the current process.
- The current process continues until it gives control back to the SystemC kernel.
- The kernel can then schedule the process waiting for the event.

------------------------------------------------------------------------------------------------------------------------

3) ZERO TIME NOTIFICATION
my_event.notify(SC_ZERO_TIME);

This schedules the event for a later delta cycle.

- Simulation time does NOT advance.

Example:
- Current simulation time = 10 ns
- my_event.notify(SC_ZERO_TIME);
- Event occurs at: 10 ns
- But in a later delta cycle.

------------------------------------------------------------------------------------------------------------------------

4) DELAYED NOTIFICATION
my_event.notify(10, SC_NS);

This schedules the event 10 ns into the future.

Example:
- Current time = 20 ns
- my_event.notify(10, SC_NS);
- Event occurs at: 30 ns

------------------------------------------------------------------------------------------------------------------------

5) WAIT FOR EVENT
wait(my_event);

This is normally used inside an SC_THREAD or SC_CTHREAD.
The process suspends until my_event is notified.

------------------------------------------------------------------------------------------------------------------------

6) WAIT FOR EITHER EVENT
wait(event1 | event2);

"|" means OR. The process wakes when either event1 OR event2 occurs.

------------------------------------------------------------------------------------------------------------------------

7) WAIT FOR BOTH EVENTS
wait(event1 & event2);

"&" means AND. The process waits until both events have occurred.

------------------------------------------------------------------------------------------------------------------------

8) CANCEL A PENDING NOTIFICATION
my_event.notify(100, SC_NS);
my_event.cancel();

cancel() cancels the pending timed notification.

------------------------------------------------------------------------------------------------------------------------

9) SC_THREAD vs SC_METHOD

SC_THREAD:
void my_thread()
{
    wait(my_event);
}

SC_METHOD:
void my_method()
{
    next_trigger(my_event);
}

------------------------------------------------------------------------------------------------------------------------

10) SC_METHOD CANNOT USE wait()

SC_METHOD(my_method);
void my_method()
{
    // wait(my_event);  <- THIS IS NOT ALLOWED
}

Instead use: next_trigger(my_event);

------------------------------------------------------------------------------------------------------------------------

11) STATIC SENSITIVITY

For SC_METHOD we can specify sensitivity:

SC_METHOD(my_method);
sensitive << event1 << event2;

This means my_method() is triggered when event1 OR event2 causes the method to be activated.

------------------------------------------------------------------------------------------------------------------------

12) DYNAMIC SENSITIVITY

Inside an SC_METHOD we can use: next_trigger(event1);
This changes the sensitivity for the next invocation of the method.

------------------------------------------------------------------------------------------------------------------------

13) sc_event DOES NOT STORE DATA

sc_event is only used for synchronization. It does NOT contain a value.

For example:
sc_signal<int> data;
sc_event data_ready;

data.write(10);
data_ready.notify();

Here:
data -> contains the actual data
data_ready -> tells another process that the data is ready

------------------------------------------------------------------------------------------------------------------------

14) SYSTEMVERILOG vs SYSTEMC

SystemVerilog             |           SystemC
------------------------------------------------------------------
event                     |           sc_event
-> event                  |           event.notify()
@event                    |           wait(event)
#10 event                 |           event.notify(10, SC_NS)
@(event1 or event2)       |           wait(event1 | event2)
@(event1 and event2)      |           wait(event1 & event2)
always_comb               |           SC_METHOD + sensitivity
dynamic event control     |           next_trigger()

------------------------------------------------------------------------------------------------------------------------

15) QUICK CHEAT SHEET

Create event:                      sc_event my_event;
Notify immediately:                my_event.notify();
Notify after zero simulation time: my_event.notify(SC_ZERO_TIME);
Notify after 10 ns:                my_event.notify(10, SC_NS);
Cancel pending notification:       my_event.cancel();
SC_THREAD waiting for event:       wait(my_event);
Wait for either:                   wait(event1 | event2);
Wait for both:                     wait(event1 & event2);
SC_METHOD dynamic sensitivity:     next_trigger(my_event);
Static sensitivity:                SC_METHOD(my_process); sensitive << my_event;
*/