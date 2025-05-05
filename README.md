
# PROJETO RISCV ([IC/FAPESP](https://bv.fapesp.br/pt/bolsas/216904/risc-v-superescalar-com-despacho-duplo-para-fpgas/))

O projeto é desenvolvido em duas frentes: [SIMULAÇÃO](SIM/README.md) e [SÍNTESE](RTL/README.md).

## IMPLEMENTAÇÕES

O alvo central do desenvolvimento são processadores que seguem o padrão RV32I, ou seja, a arquitetura RISC-V com 32bits e operações com números inteiros. Além disso, tratando-se da organização interna, a base dos processadores foi feita através de um pipeline com 5 estágios: Instruction Fetch, Instruction Decode, Execute, Memory Access e Write Back. Partindo de uma ideia modular, é possível configurar as características desejadas através dos parâmetros do processador. Para tal foi criado o arquivo SoC, que permite a utilização do processador de maneira a isolar o processador de características externas, como memórias, uart, IO, etc.
