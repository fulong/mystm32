.equ SRAMBASE,0x20000000
.equ SRAMSIZE,0x10000

.equ _sdata,(SRAMBASE)
.equ _edata,(SRAMBASE+2028*2)
.equ _sbss,(SRAMBASE+2028*4)
.equ _ebss,(SRAMBASE+2028*6)
.equ _estack,(SRAMBASE+SRAMSIZE)
