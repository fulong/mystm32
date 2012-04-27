sinclude ../var.mk
source_src := $(wildcard *.c)
source_obj := $(patsubst %.c,%.o,$(source_src))
source_h := $(wildcard *.h)

user.compiled:${source_obj} ${source_h}
	@cp *.o ../${output_dir} -rf
	@${RM} $@
	@touch $@
	

.PHONY:clean all
clean:
	@echo 正在删除sys文件夹.o文件
	-@${RM} *.o *.compiled