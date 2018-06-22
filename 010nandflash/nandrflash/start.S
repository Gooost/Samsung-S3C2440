
.text
.global _start

_start:
	b reset          /* vector 0 : reset */
	ldr pc, und_addr /* vector 4 : und */
	ldr pc, swi_addr /* vector 8 : swi */
	b halt			 /* vector 0x0c : prefetch aboot */
	b halt			 /* vector 0x10 : data abort */
	b halt			 /* vector 0x14 : reserved */
	ldr pc, irq_addr /* vector 0x18 : irq */
	b halt			 /* vector 0x1c : fiq */

und_addr:
	.word do_und

swi_addr:
	.word do_swi

irq_addr:
	.word do_irq	

do_und:
	/* 执行到这里之前:
	 * 1. lr_und保存有被中断模式中的下一条即将执行的指令的地址
	 * 2. SPSR_und保存有被中断模式的CPSR
	 * 3. CPSR中的M4-M0被设置为11011, 进入到und模式
	 * 4. 跳到0x4的地方执行程序 
	 */

	/* sp_und未设置, 先设置它 */
	ldr sp, =0x34000000

	/* 保存现场 */
	/* 在und异常处理函数中有可能会修改r0-r12, 所以先保存 */
	/* lr是异常处理完后的返回地址, 也要保存 */
	stmdb sp!, {r0-r12, lr}  
	
	/* 处理und异常 */
	mrs r0, cpsr
	ldr r1, =und_string
	bl printException
	
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^会把spsr的值恢复到cpsr里 */

und_string:
	.string "UDEF"	
.align 4

do_swi:
	/* 执行到这里之前:
	 * 1. lr_svc保存有被中断模式中的下一条即将执行的指令的地址
	 * 2. SPSR_svc保存有被中断模式的CPSR
	 * 3. CPSR中的M4-M0被设置为10011, 进入到svc模式
	 * 4. 跳到0x08的地方执行程序 
	 */

	/* sp_svc未设置, 先设置它 */
	ldr sp, =0x33e00000

	/* 保存现场 */
	/* 在swi异常处理函数中有可能会修改r0-r12, 所以先保存 */
	/* lr是异常处理完后的返回地址, 也要保存 */
	stmdb sp!, {r0-r12, lr}  

	mov r4, lr
	
	/* 处理swi异常 */
	mrs r0, cpsr
	ldr r1, =swi_string
	bl printException
	
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^会把spsr的值恢复到cpsr里 */
	
swi_string:
	.string "SWI"

.align 4

do_irq:
	/* 执行到这里之前:
	 * 1. lr_irq保存有被中断模式中的下一条即将执行的指令的地址
	 * 2. SPSR_irq保存有被中断模式的CPSR
	 * 3. CPSR中的M4-M0被设置为10010, 进入到irq模式
	 * 4. 跳到0x18的地方执行程序 
	 */

	/* sp_irq未设置, 先设置它 */
	ldr sp, =0x33d00000

	/* 保存现场 */
	/* 在irq异常处理函数中有可能会修改r0-r12, 所以先保存 */
	/* lr-4是异常处理完后的返回地址, 也要保存 */
	sub lr, lr, #4
	stmdb sp!, {r0-r12, lr}  
	
	/* 处理irq异常 */
	bl handle_irq_c
	
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^会把spsr_irq的值恢复到cpsr里 */


reset:
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

	/* 复位之后, cpu处于svc模式
	 * 现在, 切换到usr模式
	 */
	mrs r0, cpsr         /* 读出cpsr */
	bic r0, r0, #0xf     /* 修改M4-M0为0b10000, 进入usr模式 */
	bic r0, r0, #(1<<7)  /* 清除I位, 使能中断 */
	msr cpsr, r0

	/* 设置 sp_usr */
	ldr sp, =0x33f00000

	ldr pc, =uart
uart:
	bl uart_init	/*115200 8n1*/

und_code:
	.word 0xdeadc0de  /* 模拟未定义指令，触发未定义指令中断 */

	swi 0x123  /* 执行此命令, 触发SWI(Software Interrupt)异常, 进入0x8执行 */

	//bl main  /* 使用BL命令相对跳转, 程序仍然在NOR/sram执行 */
	ldr pc, =main  /* 绝对跳转, 跳到SDRAM */

halt:
	b halt


	/*怎样写位置无关码？
	最根本办法看反汇编分析问题
	1.使用相对跳转命令B/BL
	2.重定位之前不可使用绝对地址，比如不可访问全局变量/静态变量，有初始值的数组
	3.重定位之后使用绝对跳转命令跳转到runtime address，比如：ldr pc, = main
	*/



