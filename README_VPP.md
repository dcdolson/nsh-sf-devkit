Start VPP with "make run" from this directory.

Then configure the VPP with these commands to
(a) load plugin,
(b) create hops to the plugin
(c) create hops back to the TSE
(d) enable the interface

```
nsh load /home/klarose/src/nsh-sf-devkit/lib/libexample_count.so
create nsh entry nsp 200 nsi 4 md-type 1
create nsh map nsp 200 nsi 4 mapped-nsp 200 mapped-nsi 4 nsh_action pop encap-other nshsfdev 0
create nsh entry nsp 200 nsi 3 md-type 1
create nsh map nsp 200 nsi 3 mapped-nsp 200 mapped-nsi 3 nsh_action pop encap-ethernet 1 fa163eeb8918fa163e7f66eb894f
create nsh entry nsp 200 nsi 253 md-type 1
create nsh map nsp 200 nsi 253  mapped-nsp 200 mapped-nsi 253  nsh_action pop encap-other nshsfdev 0
create nsh entry nsp 200 nsi 252 md-type 1
create nsh map nsp 200 nsi 252  mapped-nsp 200 mapped-nsi 252  nsh_action pop encap-ethernet 1 fa163eeb8918fa163e7f66eb894f
set interface state GigabitEthernet0/4/0 up
```

