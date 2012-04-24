.equ SRAMBASE,0x20000000
.equ SRAMSIZE,0x5000

.equ _sidata,(SRAMBASE)			
.equ _sdata,(SRAMBASE+1024*1)
.equ _edata,(SRAMBASE+1024*2)
.equ _sbss,(SRAMBASE+1024*3)
.equ _ebss,(SRAMBASE+1024*4)
.equ _estack,(SRAMBASE+SRAMSIZE)
