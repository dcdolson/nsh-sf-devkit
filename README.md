# nsh-sf-devkit
A Service Function Development Framework

Goal: to provide a framework to implement an NSH-capable service function.

## Building

Currently this has been tested on Ubuntu

$ uname -rv
4.4.0-45-generic #66-Ubuntu SMP Wed Oct 19 14:12:37 UTC 2016

To build, you may need to install:
 * make
 * g++

After cloning the project,
```
 $ cd nsh-sf-devkit
 $ make
```

Generated object files are found in `obj` folders beneath the code.
Libraries are found in `lib`.
Executables are found in `bin` folders beneath the application code.

### Using DPDK
To use DPDK, you need to have it compiled and installed as a shared library in the system lib path.
Then, you need to compile the entire development kit with the following environment variable set to the DPDK library include path: DPDK_INCLUDE.

For example,
'''
make clean
export DPDK_INCLUDE=/usr/include/dpdk/
make
'''
Note: DPDK 2.2, which is shipped with ubuntu, does not play nicely with virtio and recent versions of qemu. If you do not unbind/rebind a virtio nic prior to starting an application, you risk having qemu kill your guest.

## Examples

These examples use the library:
 * health_echo - simply echo back health-check OAM packets.
 * count - simply forward all packets, and count the packets and bytes. Uses the OAM Demux.



## Coding Standards

Code is compiled with gcc options `-Wall -std=c++14`.

## Tips

To give a program permission to use RAW or PACKET sockets without having super-user
privilege, give capabilities to the executable: `sudo setcap cap_net_raw=pe <executable>`.

