# Processadores

O TRYonRISCV reúne duas famílias de processadores RV32I. Elas compartilham o
mesmo SoC e o mesmo fluxo de compilação e simulação, mas exploram organizações
de pipeline diferentes.

- **TORV:** emite uma instrução por ciclo e apresenta, de forma incremental,
  técnicas de encaminhamento e predição de desvios.

- **TORVS:** emite até duas instruções por ciclo e explora o paralelismo entre
  instruções com dois pipelines e diferentes configurações de despacho.

As versões são mantidas como implementações RTL independentes. Isso permite
comparar uma técnica isoladamente, executar o mesmo benchmark em arquiteturas
diferentes e observar o impacto nas métricas coletadas pela simulação.

```{toctree}
:maxdepth: 2
:caption: Processadores

torv
torvs
```
