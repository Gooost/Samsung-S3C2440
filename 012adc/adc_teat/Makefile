
objs  = start.o init.o interrupt.o nandflash.o lib1funcs.o led.o key.o uart.o timer.o string_utils.o nor_flash.o main.o

objs += lcd/font.o
objs += lcd/framebuffer.o
objs += lcd/geometry.o
objs += lcd/lcd.o
objs += lcd/lcd_4.3.o
objs += lcd/lcd_controller.o
objs += lcd/lcd_test.o
objs += lcd/s3c2440_lcd_controller.o
objs += lcd/font_8x16.o

output_elf = main.elf
output_bin = main.bin
output_dis = main.dis 
#CFLAGS = -Iinclude -march=armv4
CFLAGS = -Werror -Iinclude -march=armv4

dep_files := $(patsubst  %, .%.d, $(objs))
dep_files := $(wildcard $(dep_files)) #find the files on the desk


$(output_elf): $(objs)
	arm-linux-ld -T main.lds $(objs) libgcc.a -o $(output_elf) #make sure 4K RAM
	arm-linux-objcopy -O binary -S $(output_elf) $(output_bin)
	arm-linux-objdump -D -m arm $(output_elf) > $(output_dis)

ifneq ($(dep_files),)
include $(dep_files)
endif


%.o:%.S
	arm-linux-gcc $(CFLAGS) -c -o $@ $<
%.o:%.c
	arm-linux-gcc $(CFLAGS) -c -o $@ $<
clean:
	rm *.bin *.o *.elf *.dis


distclean:
	rm $(dep_files)


.PHONY: clean
