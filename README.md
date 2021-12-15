# tdb

A tiny debugger. Requires x64 Linux and objdump to run.

Source level debugging isn't really supported, but assembly level debugging is.

## Commands
 - `d`: disassemble the current executable
 - `s`: step one instruction
 - `c`: continue to next breakpoint
 - `b <addr>`: break at \<addr\>
 - `l`: list all breakpoints
 - `i`: dump RIP, RBP, RSP
 - `h`: display help menu
 - `q`: quit the debugger

## TODOs
1. doesn't work for a regular helloworld.c
	no support for PIC executables, recompile with -no-pie flag
2. set watchpoints
3. disable breakpoints
4. Use libdwarf!
	got it to work, but code relies on compiler generating dwarf2
	apparently still decently popular...

