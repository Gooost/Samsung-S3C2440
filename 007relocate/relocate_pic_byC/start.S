

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
	mov r1, #0
	ldr r0, [r1] /* read back byte */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? 如果相等表示是NAND启动 */
	ldr sp, =0x40000000+4096 /* 先假设是nor启动 */
	moveq sp, #4096  /* nand启动 */
	streq r0, [r1]   /* 恢复原来的值 */

	/*init sdram*/
	bl sdram_init 

	/*复制所有代码段，数据段到sdram*/
	bl copy2sdram 

	/*清楚bss段*/
	bl clean_bss 

	/*调用main*/
	//bl main				/*相对跳转，程序仍然在片内SRAM执行*/
	ldr pc, = main		/*绝对跳转，跳转到片外SDRAM，runtime addr*/
	

halt:
	b halt


	/*怎样写位置无关码？
	最根本办法看反汇编分析问题
	1.使用相对跳转命令B/BL
	2.重定位之前不可使用绝对地址，比如不可访问全局变量/静态变量，有初始值的数组
	3.重定位之后使用绝对跳转命令跳转到runtime address，比如：ldr pc, = main
	*/



