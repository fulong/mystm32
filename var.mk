#目录变量
elf_output_dir := elf_output/
output_dir := obj_output/
cpu_dir := stm32f103/
start_dir := start_code/
user_dir := user/
#命令变量
CC = arm-uclinuxeabi-gcc
CFLAGS = -Wall \
		  -march=armv7-m \
		 -mthumb \
		 -mcpu=cortex-m3 \
		 -O2 \
		 -ffunction-sections

AS = arm-uclinuxeabi-gcc 
ASFLAGS = -c \
		  -Wall \
		  -mcpu=cortex-m3 \
		  -mthumb \
		  -march=armv7-m \
		  -O2 \
		  -ffunction-sections

LD = arm-uclinuxeabi-ld
LD_FLAGS = -Tstm32f103.lds --gc-sections 

OBJCOPY_FLAGS = -O binary -S

OBJCOPY = arm-uclinuxeabi-objcopy
OBJDUMP = arm-uclinuxeabi-objdump
OBJDUMP_FLAGS = -D -m arm

