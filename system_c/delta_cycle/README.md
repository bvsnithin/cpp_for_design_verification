# SystemC Delta Cycle Examples

This folder contains standalone examples showing how SystemC processes, signal updates,
events, and delta cycles interact.

## The Mental Model for Understanding Delta Cycles

At one simulation timestamp, the kernel repeatedly performs:

1. **Evaluation** — runnable processes execute.
2. **Update** — primitive channels such as `sc_signal` commit pending values.
3. **Notification** — changed channels/events make processes runnable.
4. Repeat until quiescent(The kernel has run every currently runnable process and none are left waiting, nothing more to evaluate at the current simulation time.), then advance simulation time.

**A delta cycle is a zero time execution step** used to evaluate concurrent events without advancing time. A delta cycle consumes simulator work but no modeled time.

Note: A "Kernel" is basically the simulation engine (or simply called the scheduler) that drives the whole simulation! 
It is part of the systemc class library. It is responsible for the following: 
1. Scheduling
2. Simulation Time Management
3. Event Handling
4. Delta Cycle Resolution
5. Elaboration and Initialization

**What is a runnable process?**
A runnable process is an SC_METHOD or SC_THREAD that's been marked ready to execute in the current evaluation phase, because an event it's sensitive to just fired (a signal changed, an event got notified, a timeout elapsed, etc).

It sits in the kernel's runnable queue until the Evaluation phase, where the kernel pulls it out and actually runs it. Once run, an SC_METHOD returns immediately; an SC_THREAD runs until it hits a wait(), suspending until it becomes runnable again.

## Contents

| No. | File | Lesson |
|---:|---|---|
| 1 | `01_deferred_signal_update.cpp` | `write()` is not immediately visible |
| 2 | `02_signal_wakes_process.cpp` | A committed change wakes sensitive logic |
| 3 | `03_combinational_chain.cpp` | Signal chains propagate over several deltas |

