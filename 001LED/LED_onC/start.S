

.text
.global _start

_start:

/**close watch dog ,defalt is open*/
	ldr r0 , =0x53000000
	ldr r1 , = 0
	str r1 , [r0]


	/*set sp  Stacks*/
	ldr sp, =4096 				/*nand start*/
//	ldr sp, = 0x40000000 + 4096	/*nor start*/


	/*µ÷ÓÃmain*/
	bl main
	

halt:
	b halt



