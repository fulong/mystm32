sinclude ../var.mk
.PHONY:clean
source_src := $(wildcard *.c)
source_obj := $(patsubst %.c,%.o,$(source_src))
source_h := $(wildcard *.h)

chip.compiled:${source_obj} ${source_h}
	@cp *.o ../${output_dir} -rf
	@${RM} $@
	@touch $@
	

clean:
	@echo 正在删除chip文件夹.o文件
	-@${RM} *.o *.compiled  