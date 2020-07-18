.name " defense "
.comment " defender"

loop:   live %0
    zjmp %8

onestdelabab: st r1,6
    live %66
    ld -4,r1
    st r2,-14
    
    ld %0,r5
    zjmp %:init

slide2: zjmp %-492

slide1: live %1
    st r2,-385
    st r4,-386
defmode:   st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
    st r3,-510
deflive:  live %1
    zjmp %:defmode


init:   ld %57672703,r3
    #ld %57672560,r3
    sti r1,%:loop,%1
    sti r1,%:source,%1
    sti r1,%:source,%9
    sti r1,%:treezi,%1
    sti r1,%:gen21,%1
    sti r1,%:gen22,%1
    sti r1,%:deflive,%1
    sti r1,%:slide1,%1
    ld :deflive,r2
    ldi %:deflive,%4,r4
    ld %0,r5

source: live %1
    fork %-5
    live %1
    zjmp %:treezi

treezi:  live %1
    fork %:gen22    


gen21:  live %1     
    zjmp %:slide1
gen22:  live %1     
    zjmp %:slide2


