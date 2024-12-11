.section .data
addr: 
	.word 0

.section .text
.globl csrrw
.globl csrrs
.globl csrrc

csrrw:
	mv t0,a0
	addi t1, zero, 0x341
	beq t1, a1, .WMEPC	
	addi t1, zero, 0x342
	beq t1, a1, .WMCAUSE
	addi t1, zero, 0x300
	beq t1, a1, .WMSTATUS
	addi t1, zero, 0x305
	beq t1, a1, .WMTVEC
	addi a0, zero, -1
	j .wout
.WMEPC:
	csrrw a0,mepc,t0
	j .wout
.WMCAUSE:
	csrrw a0,mcause,t0
	j .wout
.WMSTATUS:
	csrrw a0,mstatus,t0
	j .wout
.WMTVEC:
	csrrw a0,mtvec,t0
	j .wout
.wout:
	ret
csrrs:
	mv t0,a0
	addi t1, zero, 0x341
	beq t1, a1, .SMEPC	
	addi t1, zero, 0x342
	beq t1, a1, .SMCAUSE
	addi t1, zero, 0x300
	beq t1, a1, .SMSTATUS
	addi t1, zero, 0x305
	beq t1, a1, .SMTVEC
	addi a0, zero, -1
	j .sout
.SMEPC:
	csrrs a0,mepc,t0
	j .sout
.SMCAUSE:
	csrrs a0,mcause,t0
	j .sout
.SMSTATUS:
	csrrs a0,mstatus,t0
	j .sout
.SMTVEC:
	csrrs a0,mtvec,t0
	j .sout
.sout:
	ret

csrrc:
	mv t0,a0
	addi t1, zero, 0x341
	beq t1, a1, .CMEPC	
	addi t1, zero, 0x342
	beq t1, a1, .CMCAUSE
	addi t1, zero, 0x300
	beq t1, a1, .CMSTATUS
	addi t1, zero, 0x305
	beq t1, a1, .CMTVEC
	addi a0, zero, -1
	j .cout
.CMEPC:
	csrrc a0,mepc,t0
	j .cout
.CMCAUSE:
	csrrc a0,mcause,t0
	j .cout
.CMSTATUS:
	csrrc a0,mstatus,t0
	j .cout
.CMTVEC:
	csrrc a0,mtvec,t0
	j .cout

.cout:
	ret
