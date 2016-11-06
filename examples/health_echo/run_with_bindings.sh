#!/bin/bash
# Parameters: $1  PCI address of interface.

# Find binary file relative to this script.
bin_file=$(dirname $0)/bin/health_echo
$(dirname $0)/../safe_run.sh "$bin_file" "$1"

