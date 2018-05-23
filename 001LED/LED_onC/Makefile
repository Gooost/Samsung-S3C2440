
led_on.elf: led_on.o start.o 
	arm-linux-ld -Ttext 0 start.o led_on.o -o led_on.elf
	arm-linux-objcopy -O binary -S led_on.elf led_on.bin
	arm-linux-objdump -D -m arm led_on.elf > led_on.dis
start.o:start.S
	arm-linux-gcc -c -o start.o start.S
led_on.o:led_on.c
	arm-linux-gcc -c -o led_on.o led_on.c
clean:
	rm *.bin *.o *.elf *.dis
	









