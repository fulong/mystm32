sinclude ../var.mk
.PHONY:clean
source_src := $(wildcard *.c)
source_obj := $(patsubst %.c,%.o,$(source_src))
source_h := $(wildcard *.h)

package.compiled:${source_obj} ${source_h}
	-@cp -rf ${source_obj} ../${output_dir} 
	@${RM} $@
	@touch $@
	

clean:
	@echo 正在删除package文件夹.o文件
	-@${RM} *.o  *.compiled