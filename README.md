# Scheduler

Simpler multithreaded task scheduler. This program is a real time event scheduler. It takes an initial command line argument to establish the current time and then based off of that it prints out the action requests in order. Each new request updates the current time. The reader thread takes input from stdin and then puts the input into the MinHeap. The sequencer thread takes items out of the MinHeap and schedules the appropriate time for completion. Mutex locks are enabled to maintain syncronization.

Minheap code was provided by instructor

Known Issues: Program crashes after all tasks are completed, simple solution is to exit the program immediately after last task is completed.
