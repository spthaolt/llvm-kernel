# High-level overview #

The process manager keeps a list of all the processes in the system. For now we will use a fixed-size array. Each process is represented by a **struct process** with relevant information:
  * PID
  * executable file name
  * address space (added later, with VM)
  * data and code locations in memory
  * CPU state (registers, IP) at last entrance to kernel space
  * data structures for scheduling
  * parent process
  * signal handlers and other information
  * UID and GID
  * open files

# The scheduler #

For now, the scheduler will use a simple LRU algorithm. Each running process is put into a queue when it sleeps and the next running process is taken from the same queue.