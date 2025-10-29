# 42_minitalk

A project on signal handling in C.

It involves signal processing using the functions inside signal(2) in the standard C library.

Unfortunately, Linux does not queue signals. One way to handle that is to sleep for the right amount of microseconds.

**Description:** Two binaries `./client` and `./server` must communicate with each other through signals. Where, the **client** (supplied with the server pid) sends strings to a listening **server**.

**Extras:** Have a way to receive unicode characters and the server must acknowledge the client by sending back a signal.

## Usage

Tested with:
- GCC 10.5
- C17
- Ubuntu Linux (natively and in Windows 11 WSL)

To compile `./server` and `./client`:
```sh
make
```

To test:
- Run `./server` which will display its pid and listen for signals.
- Run `./client <server_pid> <string>` which will send the string to the server.

**Note:** Extra work are in the same binaries. Though, in some cases, unicode will not print depending on terminal formatting.

## Results

TODO

- signal handling is straightforward.

## References

- **kimylamp's** [video on signals](https://www.youtube.com/watch?v=d0gS5TXarXc). A dive into how signals are processed inside the operating system.
- **Nic Barker's** [video on the UTF-8 format](https://youtu.be/vpSkBV5vydg?si=Ip12hcxW9miOvb0J) which talks about how these characters are stored in bits.
- The GNU manual on [signal(2)](https://www.man7.org/linux/man-pages/man2/signal.2.html). References on return values and smart signal structs.

> Made in C
