sinclude var.mk
compiled := sysdev.compiled start_code.compiled  user.compiled stm32f103.compiled \
			libc.compiled package.compiled chip.compiled

.PHONY: all clean $(compiled)
all:stm32f103.bin 
#######################################################
stm32f103.bin: ./$(elf_output_dir)stm32f103.elf  
	${OBJCOPY} ${OBJCOPY_FLAGS} ./$(elf_output_dir)stm32f103.elf $@
	${OBJDUMP} ${OBJDUMP_FLAGS} ./$(elf_output_dir)stm32f103.elf > ./$(elf_output_dir)stm32f103.dis
######################################################
#######################################################
./$(elf_output_dir)stm32f103.elf:$(compiled)
	@make -C obj_output

#######################################################
start_code.compiled:
	@make -C start_code
######################################################
#######################################################
package.compiled:
	@make -C package
######################################################
#######################################################
user.compiled:
	@make -C user
######################################################
#######################################################
libc.compiled:
	@make -C libc
######################################################
#######################################################
stm32f103.compiled:
	@make -C stm32f103
#############################################################################################################
sysdev.compiled:
	@make -C sysdev
######################################################
#############################################################################################################
chip.compiled:
	@make -C chip
######################################################
clean:
	-@echo "删除各子文件夹中编译出来的对象文件"
	-@${RM}  stm32f103.bin ${elf_output_dir}stm32f103.elf ${elf_output_dir}stm32f103.dis
	-@make -C start_code clean
	-@make -C user clean
	-@make -C stm32f103 clean
	-@make -C sysdev clean
	-@make -C obj_output clean		
	-@make -C libc clean		
	-@make -C package clean	
	-@make -C chip clean	
	