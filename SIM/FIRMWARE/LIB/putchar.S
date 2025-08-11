# Base address of memory-mapped IO,
# Loaded into gp at startup
.equ IO_BASE, 0x400000  

# IO-reg offsets. To read or write one of them,
# use IO_XXX(gp)
.equ IO_LEDS, 4
.equ IO_UART_DAT, 8
.equ IO_UART_CNTL, 16

.section .text
.globl putchar

putchar:
    li   t0, 1 << 9               # máscara do bit READY (bit 9)

.wait_ready:
    lw   t1, IO_UART_CNTL(gp)     # lê registrador de status
    and  t1, t1, t0               # isola o bit 9
    beqz t1, .wait_ready          # loop enquanto READY == 0

    sw   a0, IO_UART_DAT(gp)      # envia o byte (pulso de 1 ciclo)

    # Opcional: aguardar READY voltar a 0 se quiser
    # li   t0, 1 << 9
    # .busy:
    #     lw   t1, IO_UART_CNTL(gp)
    #     and  t1, t1, t0
    #     bnez t1, .busy          # espera descer

    ret


#putchar:
#   sw a0, IO_UART_DAT(gp)
#   li t0, 1<<9
#.L0:  
#   lw t1, IO_UART_CNTL(gp)
#   and t1, t1, t0
#   bnez t1, .L0
#  ret

