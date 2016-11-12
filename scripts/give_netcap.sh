#!/bin/sh
# Give capability to use raw interfaces to the specified program
setcap cap_net_raw=pe "$1"

