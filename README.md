# backtrace

Latest Change:
    Wrote a simple threaded program using OpenMP to later implement and test thread-safety. 
 
Command to Compile and Run: 
    <br/>
    `g++ *.cpp -g -rdynamic -lunwind -lunwind-x86_64 -o backtrace`
    <br/>
    `./backtrace`

    

Output without thread implementation:

    2
    works

    ./backtrace(_start+0x2d) [0x7f1bf7aae4bd]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf2) [0x7f1bf7644082]
    ./backtrace(main+0x25) [0x7f1bf7ab178a]
    ./backtrace(_Z6test_1i+0x39) [0x7f1bf7ab1880]
    ./backtrace(_Z6test_2v+0x4e) [0x7f1bf7ab18d2]
    ./backtrace(_Z15printStackTracei+0x51) [0x7f1bf7ab08b9]

    Caller:
    Callee: _start
    Caller: _start
    Callee: __libc_start_main
    Caller: __libc_start_main
    Callee: main
    Caller: main
    Callee: _Z6test_1i
    Caller: _Z6test_1i
    Callee: _Z6test_2v
    Caller: _Z6test_2v
    Callee: _Z15printStackTracei

    Parent of _start is null
    Child of _start is set to __libc_start_main
    Parent of __libc_start_main is set to _start
    Child of __libc_start_main is set to main
    Parent of main is set to __libc_start_main
    Child of main is set to _Z6test_1i
    Parent of _Z6test_1i is set to main
    Child of _Z6test_1i is set to _Z6test_2v
    Parent of _Z6test_2v is set to _Z6test_1i
    Child of _Z6test_2v is set to _Z15printStackTracei
    Parent of _Z15printStackTracei is set to _Z6test_2v
    Child of _Z15printStackTracei is null

    test2
    6

    Additional Trace:
    ./backtrace(_Z6test_3v+0x71) [0x7f1bf7ab1987]
    ./backtrace(_Z18test_4_contextTreev+0x56) [0x7f1bf7ab19e1]
    ./backtrace(_Z15printStackTracei+0x51) [0x7f1bf7ab08b9]

    Caller: _Z6test_2v
    Callee: _Z6test_3v
    Caller: _Z6test_3v
    Callee: _Z18test_4_contextTreev
    Caller: _Z18test_4_contextTreev
    Callee: _Z15printStackTracei

    Parent of _Z6test_3v is set to _Z6test_2v
    Child of _Z6test_2v is set to _Z6test_3v
    Child of _Z6test_3v is set to _Z18test_4_contextTreev
    Parent of _Z18test_4_contextTreev is set to _Z6test_3v
    Child of _Z18test_4_contextTreev is set to _Z15printStackTracei
    Parent of _Z15printStackTracei is set to _Z18test_4_contextTreev
    Child of _Z15printStackTracei is null

    context tree works

    | Function Name: _start | Memory Address: 0x7f1bf7aae4bd | Pointer: 0x7fffc52dd150 | Parent: NULL | Children: __libc_start_main,

    | Function Name: __libc_start_main | Memory Address: 0x7f1bf7644082 | Pointer: 0x7fffc52dd310 | Parent: _start | Children: main,

    | Function Name: main | Memory Address: 0x7f1bf7ab178a | Pointer: 0x7fffc52dd460 | Parent: __libc_start_main | Children: _Z6test_1i,

    | Function Name: _Z6test_1i | Memory Address: 0x7f1bf7ab1880 | Pointer: 0x7fffc52dd610 | Parent: main | Children: _Z6test_2v,

    | Function Name: _Z6test_2v | Memory Address: 0x7f1bf7ab18d2 | Pointer: 0x7fffc52dd680 | Parent: _Z6test_1i | Children: _Z15printStackTracei, _Z6test_3v,

    | Function Name: _Z15printStackTracei | Memory Address: 0x7f1bf7ab08b9 | Pointer: 0x7fffc52dd920 | Parent: _Z6test_2v | Children: NULL,

    | Function Name: _Z6test_3v | Memory Address: 0x7f1bf7ab1987 | Pointer: 0x7fffc52ddc20 | Parent: _Z6test_2v | Children: _Z18test_4_contextTreev,

    | Function Name: _Z18test_4_contextTreev | Memory Address: 0x7f1bf7ab19e1 | Pointer: 0x7fffc52dddb0 | Parent: _Z6test_3v | Children: _Z15printStackTracei,

    | Function Name: _Z15printStackTracei | Memory Address: 0x7f1bf7ab08b9 | Pointer: 0x7fffc52dde60 | Parent: _Z18test_4_contextTreev | Children: NULL,




Output with thread implementation (needs fix):

    threadedFunction1 thread_ID: 0
    2
    works

    /lib/x86_64-linux-gnu/libc.so.6(clone+0x42) [0x7f9e8a7ef132]
    /lib/x86_64-linux-gnu/libpthread.so.0(+0x8608) [0x7f9e8a4f5608]
    /lib/x86_64-linux-gnu/libgomp.so.1(+0x1a78d) [0x7f9e8a8ea78d]
    ./backtrace(+0xc176) [0x7f9e8abad176]
    ./backtrace(_Z6test_1i+0x39) [0x7f9e8abaccba]
    ./backtrace(_Z6test_2v+0x4e) [0x7f9e8abacd0c]
    ./backtrace(_Z15printStackTracei+0x51) [0x7f9e8abab979]

    Caller:
    Callee: clone
    Caller: clone
    Callee: start_thread
    Caller: start_thread
    Callee: omp_in_final
    Caller: omp_in_final
    Callee: main._omp_fn.0
    Caller: main._omp_fn.0
    Callee: _Z6test_1i
    Caller: _Z6test_1i
    Callee: _Z6test_2v
    Caller: _Z6test_2v
    Callee: _Z15printStackTracei

    Parent of clone is null
    Child of clone is set to
    Parent of  is set to clone
    Child of  is set to
    Parent of  is set to
    Child of  is set to
    Parent of  is set to
    Child of  is set to _Z6test_1i
    Parent of _Z6test_1i is set to
    Child of _Z6test_1i is set to _Z6test_2v
    Parent of _Z6test_2v is set to _Z6test_1i
    Child of _Z6test_2v is set to _Z15printStackTracei
    Parent of _Z15printStackTracei is set to _Z6test_2v
    Child of _Z15printStackTracei is null

    test2
    7

    Additional Trace:
    ./backtrace(_Z6test_3v+0x71) [0x7f9e8abacdc1]
    ./backtrace(_Z18test_4_contextTreev+0x56) [0x7f9e8abace1b]
    ./backtrace(_Z15printStackTracei+0x51) [0x7f9e8abab979]

    Caller: _Z6test_2v
    Callee: _Z6test_3v
    Caller: _Z6test_3v
    Callee: _Z18test_4_contextTreev
    Caller: _Z18test_4_contextTreev
    Callee: _Z15printStackTracei

    Parent of _Z6test_3v is set to _Z6test_2v
    Child of _Z6test_2v is set to _Z6test_3v
    Child of _Z6test_3v is set to _Z18test_4_contextTreev
    Parent of _Z18test_4_contextTreev is set to _Z6test_3v
    Child of _Z18test_4_contextTreev is set to _Z15printStackTracei
    Parent of _Z15printStackTracei is set to _Z18test_4_contextTreev
    Child of _Z15printStackTracei is null

    context tree works

    | Function Name: clone | Memory Address: 0x7f9e8a7ef132 | Pointer: 0x7f9e84000de0 | Parent: NULL | Children: ,

    | Function Name:  | Memory Address: 0x7f9e8a4f5608 | Pointer: 0x7f9e84000ee0 | Parent: clone | Children: ,

    | Function Name:  | Memory Address: 0x7f9e8a8ea78d | Pointer: 0x7f9e84001000 | Parent:  | Children: ,

    | Function Name:  | Memory Address: 0x7f9e8abad176 | Pointer: 0x7f9e840011e0 | Parent:  | Children: _Z6test_1i,

    | Function Name: _Z6test_1i | Memory Address: 0x7f9e8abaccba | Pointer: 0x7f9e84001290 | Parent:  | Children: _Z6test_2v,

    | Function Name: _Z6test_2v | Memory Address: 0x7f9e8abacd0c | Pointer: 0x7f9e84001510 | Parent: _Z6test_1i | Children: _Z15printStackTracei, _Z6test_3v,

    | Function Name: _Z15printStackTracei | Memory Address: 0x7f9e8abab979 | Pointer: 0x7f9e840015a0 | Parent: _Z6test_2v | Children: NULL,

    | Function Name: _Z6test_3v | Memory Address: 0x7f9e8abacdc1 | Pointer: 0x7f9e84001960 | Parent: _Z6test_2v | Children: _Z18test_4_contextTreev,

    | Function Name: _Z18test_4_contextTreev | Memory Address: 0x7f9e8abace1b | Pointer: 0x7f9e84001aa0 | Parent: _Z6test_3v | Children: _Z15printStackTracei,

    | Function Name: _Z15printStackTracei | Memory Address: 0x7f9e8abab979 | Pointer: 0x7f9e84001be0 | Parent: _Z18test_4_contextTreev | Children: NULL,