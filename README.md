DS-OS
=====

This is a small operating system written in 8086 assembly.
It was written in the late 90's and was not under version
control.

The operating system is in working order has comes complete
with:

* kernel / simple file system / interrupt based API
* command interpreter
* boot loader
* sample user program (hex dumper)
* a PS/2 mouse driver

Work on this project stopped around 1999, but the OS can
still be run today on a PC-compatible machine or under
under a virtual machine such as Virtual Box.  For more
information and some documentation please see the project's
[website](http://www.itfromterabit.net/dsos) (which was
also created in the late 90's and resurrected).

Running in VirtualBox
---------------------

To run this operating system in VirtualBox simply create
a new VM (choosing the "Other"/"Other Unknown" categories),
along with a virtual disk (which will not be used).  Then,
Go into the Settings for the VM, select "Storage", then
add a new floppy controller, then add the "image.flp" file
as a disk.  Then just boot the VM and it should work.
