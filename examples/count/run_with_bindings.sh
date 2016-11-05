#!/bin/bash

#bounce stuff because yeah
dpdk_nic_bind -u $1
dpdk_nic_bind -b virtio-pci $1
dpdk_nic_bind -u $1

bin/dpdk_count -w $1 --
