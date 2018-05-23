

.text
.global _start

_start:

	/**close watch dog ,defalt is open*/
	ldr r0 , =0x53000000
	ldr r1 , = 0
	str r1 , [r0]
	/*set MPLL,FCLK:HCLK:PCLK =400M:100M:50M */
	/*LOCKTIME (0x4C000000 )reste value 0xFFFFFFFF*/
	ldr r0, = 0x4C000000
	ldr r1, = 0xFFFFFFFF
	str r1,[r0]

	/*CLKDIVN (0x4C000014 ) = 0x5,tFCLK:tHCLK:tPCLK = 1:4:8*/
	ldr r0, = 0x4C000014
	ldr r1, = 0x5
	str r1,[r0]

	/*set cpu asynchronous bus mode*/
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000  //1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/*MPLLCON  (0x4C000004  ) = (92<<12)|(1<<4)|(1<<0) */
	ldr r0, = 0x4C000004
	ldr r1, = (92<<12)|(1<<4)|(1<<0)
	str r1,[r0]


	/*set sp  Stacks*/
	ldr sp, =4096 				/*nand start*/
//	ldr sp, = 0x40000000 + 4096	/*nor start*/


	/*µ÷ÓÃmain*/
	bl main
	

halt:
	b halt



