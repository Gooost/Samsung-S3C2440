
objs  = start.o led.o key.o main.o

output_elf = main.elf
output_bin = main.bin
output_dis = main.dis 
CFLAGS = -Werror -Iinclude

dep_files := $(patsubst  %, .%.d, $(objs))
dep_files := $(wildcard $(dep_files)) #find the files on the desk


$(output_elf): $(objs)
	arm-linux-ld -Ttext 0 $(objs) -o $(output_elf)
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







##objs  = led_on.o start.o
##dep_files := $(patsubst  %, .%.d, $(objs))
##dep_files := $(wildcard $(dep_files)) #find the files on the desk

##CFLAGS = -Werror -Iinclude

##test: $(objs)
##	arm-linux-ld -Ttext 0 $^ -o led_on.elf
##	arm-linux-objcopy -O binary -S led_on.elf led_on.bin
##	arm-linux-objdump -D -m arm led_on.elf > led_on.dis
#ifneq ($(dep_files),)
#include $(dep_files)
#endif
##start.o:start.S
##	arm-linux-gcc -c -o start.o start.S
##%.o:%.c
##	arm-linux-gcc $(CFLAGS) -c -o $@ $<	#-MD -MF .$@.d


##clean:
##	rm *.bin *.o *.elf *.dis
##distclean:
##	rm $(dep_files)

##.PHONY: clean