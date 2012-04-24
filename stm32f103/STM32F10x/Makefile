sinclude ../../var.mk 
stm32_src := $(wildcard *.c)
stm32_obj := $(patsubst %.c,%.o,$(stm32_src)) 
stm32_h := $(wildcard *.h) 
.PHONY: clean
compiled:$(stm32_obj) $(stm32_h)  
	@cp *.o .. 
	@${RM} $@
	@touch $@
	 
clean:
	@${RM} *.o compiled