# Software

O software do TRYonRISCV é executado diretamente sobre o hardware, sem sistema
operacional. Por isso, o projeto precisa definir não apenas o programa
principal, mas também seu mapa de memória, o código de inicialização e as
funções básicas usadas para produzir saída.

Esta seção acompanha o processo do nível mais alto para o mais baixo:

1. comandos e regras usados para construir os programas;
2. organização do executável pelo linker script;
3. inicialização do ambiente C e implementação da saída;
4. benchmarks disponíveis.

```{toctree}
:maxdepth: 2
:caption: Software

compilation
linker-script
runtime
benchmarks
```
