# TRYonRISCV ([IC/FAPESP](https://bv.fapesp.br/pt/bolsas/216904/risc-v-superescalar-com-despacho-duplo-para-fpgas/))

## Motivação
TRYonRISCV é um projeto que foi desenvolvido com o intuito de aprender e desenvolver conceitos de Hardware, ligados ao design de processadores. 
A escolha da arquitetura RISC-V, com sua crescente relevância no cenário, se tornou óbvia por possuir tanto uma comunidade muito ativa, com diversos projetos, 
quanto ferramentas úteis que permitem uma melhor exploração da construção de hardware.

## Usando o repositório

Para começar a usar o repositório recomendo a leitura da documentação em: link_read_the_docs.

## Toolchain RISC-V

O projeto disponibiliza uma toolchain GNU RISC-V pré-compilada nas
[GitHub Releases](https://github.com/arruk/TRYonRISCV/releases/latest).

A distribuição atual foi compilada e testada para Linux x86_64 em Debian 13, 
utilizando a release `2026.07.15` da `riscv-gnu-toolchain`. Ela inclui GCC,
Binutils, GDB e Newlib, com suporte às seguintes configurações:

- `rv32i/ilp32`
- `rv32imafd/ilp32`
- `rv64gc/lp64d`

O compilador utiliza o prefixo `riscv64-unknown-elf-`. O arquivo de checksum
SHA-256 é disponibilizado junto ao pacote.

Instruções de instalação, requisitos de compatibilidade e compilação da
toolchain a partir do código-fonte estão disponíveis na documentação do projeto.
