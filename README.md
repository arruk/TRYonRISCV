# TRYonRISCV ([IC/FAPESP](https://bv.fapesp.br/pt/bolsas/216904/risc-v-superescalar-com-despacho-duplo-para-fpgas/))

## Motivação
TRYonRISCV é um projeto que foi desenvolvido com o intuito de aprender e desenvolver conceitos de Hardware, ligados ao design de processadores. 
A escolha da arquitetura RISC-V, com sua crescente relevância no cenário, se tornou óbvia por possuir tanto uma comunidade muito ativa, com diversos projetos, 
quanto ferramentas úteis que permitem uma melhor exploração da construção de hardware.

## Usando o repositório

Para começar a usar o repositório recomendo a leitura da documentação em: https://tryonriscv.readthedocs.io.

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

## Publicações

Os trabalhos a seguir foram desenvolvidos a partir dos resultados obtidos neste
repositório:

- Lucas Arruk Mendes, Maurício Figueiredo e Ricardo Menotti. **[TORVS: A
  Lightweight Dual-Issue Superscalar RISC-V Core for FPGA-Based
  Systems](https://doi.org/10.1109/SBESC68008.2025.11288856)**. *2025 XV
  Symposium on Computing Systems Engineering (SBESC)*, páginas 1–6, IEEE, 2025.

- Lucas Arruk Mendes, Maurício Figueiredo e Ricardo Menotti. **[Análise de
  técnicas de predição de desvio sob a arquitetura
  RISC-V](https://doi.org/10.5753/sscad_estendido.2024.244790)**. *Simpósio em
  Sistemas Computacionais de Alto Desempenho (SSCAD)*, páginas 9–16, SBC, 2024.
