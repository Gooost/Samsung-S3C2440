

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
	cmp r1, r2   /* r1==r2? �����ȱ�ʾ��NAND���� */
	ldr sp, =0x40000000+4096 /* �ȼ�����nor���� */
	moveq sp, #4096  /* nand���� */
	streq r0, [r1]   /* �ָ�ԭ����ֵ */

	/*init sdram*/
	bl sdram_init 

	/*�������д���Σ����ݶε�sdram*/
	bl copy2sdram 

	/*���bss��*/
	bl clean_bss 

	/*����main*/
	//bl main				/*�����ת��������Ȼ��Ƭ��SRAMִ��*/
	ldr pc, = main		/*������ת����ת��Ƭ��SDRAM��runtime addr*/
	

halt:
	b halt


	/*����дλ���޹��룿
	������취��������������
	1.ʹ�������ת����B/BL
	2.�ض�λ֮ǰ����ʹ�þ��Ե�ַ�����粻�ɷ���ȫ�ֱ���/��̬�������г�ʼֵ������
	3.�ض�λ֮��ʹ�þ�����ת������ת��runtime address�����磺ldr pc, = main
	*/


