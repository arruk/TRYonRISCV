.section .text
.globl change 
.globl read 

change:
	sw a0, 16(gp)

read:
	lw a0, 0(gp)	
