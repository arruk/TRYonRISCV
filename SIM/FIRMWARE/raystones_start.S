.equ IO_BASE, 0x400000
.section .text
.globl start
start:
        mv a0, sp
        li sp,0x20000

        addi sp,sp,-16
        sw ra, 8(sp)
        sw a0, 12(sp)

        call main

        lw a0, 12(sp)
        lw ra, 8(sp)

        mv sp, a0

        jalr ra

