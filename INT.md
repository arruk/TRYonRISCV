Conjunto de Instruções da Arquitetura de Modo Privilegiado.

- Níveis de Privilégio:
	Níveis de privilégio são usados para prover proteção entre diferentes componentes da pilha do software(??), e tentativas de realizar operações não permitidas pelo modo de privilégio atual fará com que uma exceção seja levantada.
	O nível de máquina(machine-mode, M-mode) tem os maiores privilégios e é o único nível de privilégio obrigatório para uma plataforma de hardware RISC-V. Os modos de usuário (U-mode) e supervisor(S-mode) são destinados para o uso de aplicações convencionais e uso de sistemas operacionais, respectivamente.
	Cada nível de privilégio possui um conjunto básico de extenções ISA privilegiadas. Ainda assim, todos as implementações de hardware devem fornecer M-mode, já que é o único modo sem restrições do acesso à maquina. A implementação mais simples terá suporte ao M-mode, porém, não terá proteção contra códigos de aplicação incorretos ou maliciosos.
	Uma hart(hardware thread????) geralmente roda em U-mode até que alguma TRAP force a troca para o TRAP HANDLER, que geralmente roda em níveis superiores de privilégio. O hart então irá executar o TRAP HANDLER, que eventualmente irá retomar a execução na instrução que foi presa(TRAPPED) em modo usuário(U-mode).

- Modo de DEBUG:
	O modo DEBUG(D-mode) pode ser considerado um modo de privilégio adicional, com ainda mais acesso que o M-mode.

- CSRs (Control and Status Registers)
	O principal código de operação (opcode) SYSTEM é usado para codificar todas as instruções privilegiadas no ISA do RISC-V. Estas instruções podem ser divididas em duas classes: aquelas que leem-modificam-escrevem nos registradores de controle e status (CSRs) de maneira atômica (definidos na extensão Zicsr do ISA sem privilégios), e todo o resto das instruções privilegiadas.
	
- Convenções de Mapeamento de Endereços dos CSRs.
	O ISA padrão do RISC-V separada um espaço de 12-bits de codificação(csr[11:0]) para até 4096 CSRs. Por convenção, os 4 bits mais significativos do endereçamento(csr[11:8]) são utilizados para codificar a acessibilidade de leitura e escrita dos CSRs de acordo com os níveis de privilégio descritos acima. Os dois primeiros bits(csr[11:10]) indicam se o registro é leitura/escrita (00,01 ou 10) ou apenas leitura (11). Os próximos dois bits(csr[9:8]) codificam o menor nível de privilégio que tem acesso ao CSR.
	CSRs com modo usuário e sem privilégio: 0x000 - 0xCFF, csr[9:8]=2'b00;
	CSRs com nível de supervisor: 0x100 - 0xDFF, csr[9:8]=2'b01;
	CSRs com nível de hipervisor: 0x200 - 0xEFF, csr[9:8]=2'b10;
	CSRs com nível de máquina:    0x300 - 0xFFF, csr[9:8]=2'b11;
