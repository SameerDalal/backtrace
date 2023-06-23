# backtrace


Command: 
    `# g++ backtrace.cpp ContextNode.cpp -o backtrace -g -rdynamic`
    `# ./backtrace`

Output when run: 

    2
    works

    ./backtrace(_start+0x2e) [0x7f5a1d19a3de]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7f5a1cd74083]
    ./backtrace(main+0x17) [0x7f5a1d19a9a9]
    ./backtrace(_Z3fooi+0x34) [0x7f5a1d19aa52]
    ./backtrace(_Z3barv+0x54) [0x7f5a1d19aaa9]
    ./backtrace(_Z15printStackTraceii+0x49) [0x7f5a1d19a4e2]
    test2
    6
    ./backtrace(_Z9otherTestv+0x5e) [0x7f5a1d19ab0f]
    ./backtrace(_Z14otherOtherTestv+0x1d) [0x7f5a1d19ab2f]
