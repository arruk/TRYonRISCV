# Setup Inicial

## Pré-requisitos

O TRYonRISCV foi projetado e testado em sistemas Linux x86_64. Outros sistemas
podem funcionar, mas ainda não fazem parte do ambiente regularmente validado
pelo projeto. Esta seção considera apenas a compilação dos benchmarks e a
simulação; as ferramentas necessárias para síntese em FPGA são apresentadas em
uma seção própria.

O fluxo básico utiliza as seguintes ferramentas:

- Git, para obter o repositório e suas dependências;
- GNU Make, para coordenar a compilação e a simulação;
- um compilador C++ para o host, utilizado pelo Verilator;
- Verilator, para converter o RTL em um simulador executável;
- Python 3, utilizado por ferramentas auxiliares do Verilator;
- `curl`, `tar`, `xz` e `sha256sum`, para baixar, extrair e verificar a
  toolchain pré-compilada;
- uma GNU toolchain RISC-V com Newlib e suporte a `rv32i/ilp32`.

Em distribuições baseadas em Debian ou Ubuntu, as dependências principais podem
ser instaladas com:

```bash
sudo apt update
sudo apt install build-essential git make verilator python3 curl xz-utils
```

O comando `make print`, disponível no diretório `sim`, utiliza adicionalmente o
[Miller](https://miller.readthedocs.io/) para apresentar o arquivo CSV como uma
tabela. Essa dependência é opcional:

```bash
sudo apt install miller
```

## Toolchain RISC-V

Os benchmarks são compilados para `rv32i/ilp32` e esperam ferramentas com o
prefixo `riscv64-unknown-elf-`. Apesar do nome, uma toolchain multilib com esse
prefixo também pode gerar programas RV32I.

Há duas formas de obter uma toolchain compatível.

### Opção 1: utilizar a release pré-compilada

A forma mais rápida é baixar o pacote e seu arquivo `.sha256` na página de
[releases do TRYonRISCV](https://github.com/arruk/TRYonRISCV/releases/latest).
A distribuição fornecida foi compilada para Linux x86_64 no Debian 13; sistemas
com versões mais antigas da glibc podem não ser compatíveis.

Com os dois arquivos no diretório raiz do repositório, verifique a integridade
do pacote:

```bash
sha256sum -c tryonriscv-toolchain-2026.07.15-rv32i-debian13-x86_64.tar.xz.sha256
```

O comando compara o pacote baixado com o checksum publicado na release. Em
seguida, extraia a toolchain em `.tools/riscv`:

```bash
mkdir -p .tools
tar -xJf tryonriscv-toolchain-2026.07.15-rv32i-debian13-x86_64.tar.xz \
    -C .tools
```

### Opção 2: compilar a toolchain localmente

Quando a release não for compatível com o sistema utilizado, a toolchain pode
ser compilada localmente. Recomenda-se consultar primeiro o
[README oficial da RISC-V GNU Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain),
pois ele contém a lista atualizada de dependências e instruções para diferentes
distribuições.

Em Debian ou Ubuntu, instale as dependências recomendadas pelo projeto
upstream:

```bash
sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip \
    python3-tomli libmpc-dev libmpfr-dev libgmp-dev gawk build-essential \
    bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev \
    ninja-build git cmake libglib2.0-dev libslirp-dev libncurses-dev
```

Esse comando instala os programas e bibliotecas necessários para construir GCC,
Binutils, GDB e Newlib.

Na raiz do TRYonRISCV, salve o caminho do repositório, crie o diretório de
fontes e clone a versão utilizada pelo projeto:

```bash
REPO_ROOT="$(pwd)"
mkdir -p .tools/src
git clone --depth 1 --branch 2026.07.15 \
    https://github.com/riscv-collab/riscv-gnu-toolchain.git \
    .tools/src/riscv-gnu-toolchain
cd .tools/src/riscv-gnu-toolchain
```

Os comandos criam uma cópia local e fixada da versão upstream. Em seguida,
baixe sequencialmente os componentes usados no build:

```bash
git submodule update --init --depth 1 binutils
git submodule update --init --depth 1 gcc
git submodule update --init --depth 1 newlib
git submodule update --init --depth 1 gdb
```

O download sequencial reduz a possibilidade de bloqueios por excesso de
requisições aos servidores dos projetos. Configure então o diretório de
instalação e as variantes multilib necessárias:

```bash
./configure \
    --prefix="$REPO_ROOT/.tools/riscv" \
    --with-multilib-generator="rv32i-ilp32--;rv32imafd-ilp32--"
```

Esse comando prepara uma toolchain Newlib com suporte explícito a RV32I. Por
fim, inicie a compilação utilizando os processadores disponíveis no host:

```bash
make -j"$(nproc)"
```

O build pode levar um tempo considerável e requer vários gigabytes de espaço em
disco. Ao terminar, a toolchain estará instalada em `.tools/riscv`.

## Configuração do ambiente

Para disponibilizar a toolchain no terminal atual, entre na raiz do repositório
e carregue o script de ambiente:

```bash
cd /caminho/para/TRYonRISCV
source scripts/env.sh
```

O script define `RISCV` como `<repositório>/.tools/riscv` e adiciona o diretório
de executáveis ao `PATH`. Ele deve ser carregado novamente ao abrir um novo
terminal.

Caso a toolchain tenha sido instalada em outro local, altere o caminho definido
em `scripts/env.sh` ou configure diretamente as variáveis:

```bash
export RISCV=/caminho/para/riscv
export PATH="$RISCV/bin:$PATH"
```

O suporte a RV32I pode ser confirmado com:

```bash
riscv64-unknown-elf-gcc -print-multi-lib | grep 'rv32i/ilp32'
```

## Primeiro teste

Com o ambiente configurado, execute o fluxo padrão de simulação:

```bash
cd sim
make
```

Na primeira execução, esse comando:

1. compila o benchmark Dhrystone para `rv32i/ilp32`;
2. gera as imagens `PROGROM` e `DATARAM` utilizadas pelas memórias do SoC;
3. utiliza o Verilator e o compilador C++ do host para construir o simulador;
4. executa o Dhrystone no core `torvs7C`, usando as configurações padrão.

Uma execução bem-sucedida apresenta no terminal os resultados do Dhrystone,
incluindo CPI, número de instruções, ciclos e DMIPS/MHz. Outros cores,
benchmarks e configurações podem ser consultados com:

```bash
make help
```
