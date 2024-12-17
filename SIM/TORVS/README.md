# TORVS (Try On RISC-V Superscalar)

- torvs1.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- verificado pelos três benchmarks

- torvs1.1.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R, Imm, LUI e AUIPC no pipeline B
	- verificado pelos três benchmarks

- torvs2.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding apenas do pipeline A para A (A-\>A)
	- verificado pelos três benchmarks

- torvs3.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- verificado pelos três benchmarks

- torvs4.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- verificado pelos três benchmarks

- torvs5.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- verificado pelos três benchmarks

- torvs6.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- JAL nao causa mais bolhas
	- verificado pelos três benchmarks

- torvs7.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- JAL nao causa mais bolhas
	- predição de desvio BTFNT
	- verificado pelos três benchmarks
	- torvs7p1.sv adiciona LUI e AUIPC no pipeline B

- torvs8.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- JAL nao causa mais bolhas
	- predição de desvio dinamica, bimodal 2bits
	- verificado pelos três benchmarks

- torvs9.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- JAL nao causa mais bolhas
	- predição de desvio dinamica, gselect e gshare
	- verificado pelos três benchmarks
	- torvs9p1.sv adiciona LUI e AUIPC no pipeline B

