sinclude  ../var.mk
.PHONY: clean
obj := $(wildcard *.o)
stm32f103.compiled:$(obj)
	@make -C STM32F10x
	@make -C CoreSupport
	@cp *.o ../${output_dir} -rf
	@${RM} $@
	@touch $@


clean:
	@echo 正在删除stm32f103文件夹.o文件
	@${RM} *.o *.compiled
	@make -C STM32F10x clean
	@make -C CoreSupport clean
	