.equ SRAMBASE,0x20000000
.equ SRAMSIZE,0x5000

.equ _sdata,(SRAMBASE)
.equ _edata,(SRAMBASE+1024*2)
.equ _sbss,(SRAMBASE+1024*4)
.equ _ebss,(SRAMBASE+1024*6)
.equ _estack,(SRAMBASE+SRAMSIZE)
