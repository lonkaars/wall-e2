# shared code

this is the subdirectory for all code that is shared between the robot code and
the client code. to use these, include the .h files with a relative path (e.g.
`#include "../shared/consts.h"`). makefiles should add `include
../shared/makefile` to add the .c and .h files to `$SOURCES` and `$HEADERS` in
the makefile targets (this is already done for the robot and client
subdirectories).
