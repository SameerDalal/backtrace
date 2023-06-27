# backtrace
 
Command: 
    <br/>
    `g++ backtrace.cpp ContextNode.cpp ContextTree.cpp -g -rdynamic -o backtrace` 
    <br/>
    or
    `g++ *.cpp -g -rdynamic -o backtrace`
    <br/>
    `./backtrace`

Output when run:

    2    
    works

    ./backtrace(_start+0x2e) [0x7fc6060f03be]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7fc605cc4083]
    ./backtrace(main+0x26) [0x7fc6060f09f2]
    ./backtrace(_Z3fooi+0x34) [0x7fc6060f0ae2]
    ./backtrace(_Z3barv+0x54) [0x7fc6060f0b39]
    ./backtrace(_Z15printStackTraceii+0x49) [0x7fc6060f04c2]
    test2
    6
    ./backtrace(_Z9otherTestv+0x5e) [0x7fc6060f0b9f]
    ./backtrace(_Z14otherOtherTestv+0x34) [0x7fc6060f0bd6]
    context tree works
