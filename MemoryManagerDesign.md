# Basic functions #

  * **page\_alloc** allocates a free page somewhere in physical memory and returns the address
  * **page\_free** returns a page to the list of free regions
  * **set\_region\_reserved** prevents the MM from allocating a physical page using **page\_alloc**; used in initialization code
  * **set\_region\_available** adds a region of RAM to the list of available pages

GRUB gives us a map of all available RAM regions. The first step is to reserve a certain portion of this RAM for the stuff that are already loaded (the kernel and its' data structures) and then set the rest as available. For now, the kernel is laid out at 0x100000 (address 1MB) so the first few pages will be reserved (the number is hardcoded).

# Ideas #

For now, we will only use physical memory, no virtual memory. Later on, we will add address spaces and processes. We'll need a function that allocates a new address space, or maybe even an entire new process.