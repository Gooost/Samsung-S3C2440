
objs  = start.o lib1funcs.o init.o led.o key.o uart.o interrupt.o timer.o main.o

output_elf = main.elf
output_bin = main.bin
output_dis = main.dis 
CFLAGS = -Werror -Iinclude

dep_files := $(patsubst  %, .%.d, $(objs))
dep_files := $(wildcard $(dep_files)) #find the files on the desk


$(output_elf): $(objs)
	arm-linux-ld -T main.lds $(objs) -o $(output_elf) #make sure 4K RAM
	arm-linux-objcopy -O binary -S $(output_elf) $(output_bin)
	arm-linux-objdump -D -m arm $(output_elf) > $(output_dis)

ifneq ($(dep_files),)
include $(dep_files)
endif


%.o:%.S
	arm-linux-gcc $(CFLAGS) -c -o $@ $<
%.o:%.c
	arm-linux-gcc $(CFLAGS) -c -o $@ $< -MD -MF .$@.d
clean:
	rm *.bin *.o *.elf *.dis

distclean:
	rm $(dep_files)


.PHONY: clean
