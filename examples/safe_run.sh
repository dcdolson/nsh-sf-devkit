#!/bin/bash
# Parameters: $1  DPDK program to run
# Parameters: $2  PCI address of interface.

if [ $# -ne 2 -o "$1" = "" -o "$2" = "" ] ; then
    echo "Usage: $0 <dpdk program> <interface PCI address>" >&2
    exit 1
fi

# Find binary file relative to this script.
bin_file=$1
if [ ! -x "$bin_file" ] ; then
    echo "Cannot find executable file $bin_file" >&2
    exit 1
fi

# Clean up possible bad DPDK state.
dpdk_nic_bind -u "$2"
dpdk_nic_bind -b virtio-pci "$2"
dpdk_nic_bind -u "$2"

$bin_file --dpdk-pci-addr "$2" --

