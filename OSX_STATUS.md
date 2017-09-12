
* llvm tier not working

Looks like the in memory MachO object is being generated incorrectly.  Most symbols are of "unknown" type,
and have addr = 0, size = something large.  Hopefully updating llvm will fix it?

* unwinding not working

There are two parts to unwinding, neither is working:

C++ unwinding (cxx_unwind.cpp): right now the code is globally disabled but some portions of it could be enabled.
The real problem here is unwind_loop, which uses the non-OSX libunwind.  need to figure out a way to implement it
all without libunwind (or if possible using OSX's).

Python unwinding (src/platform/unwinding/*): The python unwinding code has a lot of functions that introspect the
python stack and so are indirectly tied to unwinding, but they should be moved out.

Ideally there is one C++ implementation (initially sitting on top of libunwind, with other platform implementations)
in platform/unwinding/*.  Both c++ unwinding and python unwinding would be implemented in terms of this
unwinding implementation, with no direct libunwind dependencies outside of src/platform.

* no MAP_32BIT on OSX

There looks to be some assumptions built into the baseline jit about the maximum size of immediate operands.
pyston uses MAP_32BIT for linux, but this doesn't exist on OSX.  Also text segment addresses are already mapped
> 32bits, so any function pointers pointing to runtime functions will need to be 8 bytes.
