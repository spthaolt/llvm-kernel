# Introduction #

In POSIX systems, the TTY subsystem handles basic text input and output for processes. The difficulty lies in the issue that a system can have more than one text console, so the TTY subsystem must provide multiplexing of the input and output from the processes to the consoles and vice-versa. There are different types of consoles with different types of features, such as keyboard/display terminals and serial lines.

The subsystem is split into a generic frontend that handles the translation for all the types of devices and one or more backend drivers for each input or output devices, like the keyboard driver, VESA framebuffer driver or the serial line driver. The frontend handles the OS and process-specific state and handles all the operations that user-space clients need.

# The frontend #

POSIX programs use 2 different channels to output and input user data: the default stdin/out/err file descriptors and the controlling terminal. These are inherited from the parent process on a **fork** or **exec** call and can be changed using **dup** and **dup2** for the file descriptors or **setsid** for the controlling terminal. **setsid** creates a new session for the current process, resetting the controlling terminal to **NULL**. The next time the process opens any TTY device with **open** without the **O\_NOCTTY** flag, the controlling terminal is set. Most often, the application opens **/dev/tty**.

All POSIX systems provide some special files:
  * **/dev/ttyXY** is a text input/output terminal; if X is the character **S**, then the terminal is a serial device
  * **/dev/tty** is the controlling terminal for the current process; can be used to reopen the standard input and output if they have been redirected
  * **/dev/console** is a link to the system console

These devices must support **read** and **write** calls for direct IO and **ioctl** for communication settings. The frontend also handles special keys and commands from the user, like _Ctrl-C_ and _Ctrl-Z_.

# The backend #

The backend handles the device-specific conversion from line-based input/output and ioctl's to raw characters and scancodes supported by the hardware.

The keyboard driver for the console is responsible for converting keyboard scancodes into text that can be read by the application. The driver must also keep track of the status of special keys (like _Ctrl_, _Alt_ and _Num Lock_) and activate the LEDs corresponding to the status. The driver handles interrupts from the keyboard and buffers the characters until the process starts a read. Optionally, the keyboard driver can also recognize keymaps for multilingual keyboard support.

The VESA display driver buffers write requests from userspace and converts them into writes to the screen, using double-buffering. It is also responsible for scrolling and moving the display cursor on **CR/LF**. Display drivers for POSIX-compliant OSes must also handle several ANSI escape codes that move the cursor around and set various character attributes.


# References #

  * Single Unix Specification http://www.unix.org/single_unix_specification/
  * LXR Linux http://lxr.linux.no/#linux+v2.6.32/