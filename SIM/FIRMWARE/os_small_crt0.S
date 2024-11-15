.equ IO_BASE, 0x400000  

.section .text
.extern exception
.extern p_exit
.globl start
start:
        li   gp,IO_BASE
	li   sp,0x40000
	
	la a0,expt 
	csrrw a1, mtvec, a0

	call main
	jal ra, 0
	call p_exit

	ebreak

r_start:
        li   gp,IO_BASE
        li   sp,0x40000

        la a0,expt
        csrrw a1, mtvec, a0

        call main
        jal ra, 0x10000
        call p_exit

        ebreak

c_start:
        li   gp,IO_BASE
        li   sp,0x40000

        la a0,expt
        csrrw a1, mtvec, a0

        call main
        jal ra, 0x20000
        call p_exit

        ebreak


expt:
	li sp, 0x40000
	csrrs a0, mcause, zero
	
	addi sp, sp, -4
	sw a0, 0(sp)

	call exception

	lw a0, 0(sp)
	addi sp, sp, 4

	addi t0, zero, 3
	bne t0, a0, exit_expt
		
	addi t2, zero, 2 
	la t0, _current_exec
	lw t1, 0(t0)
	beq t1, t2, exit_expt

	addi t1, t1, 1
	sw t1, 0(t0)

	addi t0, zero, 1
	beq t1, t0, c_start

	j r_start

exit_expt:
	j halt	


_current_exec:
	.word 0
