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


## Coding Standards

Code is compiled with gcc options `-Wall -std=c++14`.

