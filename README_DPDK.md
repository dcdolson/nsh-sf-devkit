# Instructions for Compiling with DPDK support

These instructions pertain to compiling with DPDK 2.2, which is the current version shipped with Ubuntu.

Note: DPDK 2.2, does not play nicely with virtio and recent versions of qemu. 
If you do not unbind/rebind a virtio nic prior to starting an application, you risk having qemu kill your guest.
The run_with_bindings.sh scripts does this.


## Installing DPDK

```
sudo apt-get install dpdk dpdk-dev libdpdk-dev
```

Edit `/etc/dpdk/dpdk.conf` to assign 64 2M hugepages.
```
NR_2M_PAGES=64
```

Reboot for the huge-pages configuration to be applied.


## Building with DPDK support

Compile the entire development kit with the following environment variable set to the DPDK library include path: DPDK_INCLUDE.

```
make clean
export DPDK_INCLUDE=/usr/include/dpdk/
make
```

## Running with DPDK interfaces

The examples are implemented to use either AF_PACKET or DPDK
interface types based on command-line args.

Invoke the examples with the `--dpdk-pci-addr` option to select
the use of DPDK and specify the PCI address of the interface.

The run_with_bindings script should be used to properly clean up
DPDK before using it. (This works around some DPDK bugs.)

For example,
```
examples/count/run_with_bindings.sh 0000:00:04.0
```

