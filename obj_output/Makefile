include ../var.mk
aim_elf = stm32f103.elf
source_obj := $(wildcard *.o)

lded: ${source_obj}
	${LD} ${LD_FLAGS} -o ../${elf_output_dir}${aim_elf} ${source_obj}	
	@${RM} $@
	@touch $@

.PHONY: clean
clean:
	-@$(RM) lded *.o