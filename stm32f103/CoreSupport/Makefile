sinclude ../../var.mk 
core_src = $(wildcard *.c)
core_obj =  $(patsubst %.c,%.o,$(core_src))
core_h = $(wildcard *.h) 
.PHONY:all clean
compiled:$(core_obj) $(core_h) 
	@cp *.o .. 
	@${RM} $@
	@touch $@
	
clean:
	@${RM} *.o compiled