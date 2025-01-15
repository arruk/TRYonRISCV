# TORVS (Try On RISC-V Superscalar)

- torvs1.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- verificado pelos três benchmarks
	- verificado na primer25k
	- torvs1p1.sv adiciona LUI e AUIPC no pipeline B (primer25k check)
	- torvs1p2.sv adiciona LUI, AUIPC e STOREs no pipeline B (primer25k check)
	- torvs1p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A (primer25k check)
	- torvs1p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A (primer25k check)
	- torvs1p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A (primer25k check)

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
	- verificado na primer25k
	- torvs5p1.sv adiciona LUI e AUIPC no pipeline B
    - torvs5p2.sv adiciona LUI, AUIPC e STOREs no pipeline B
    - torvs5p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A
    - torvs5p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A
    - torvs5p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A


- torvs6.sv
	- despacho duplo simples (pipelines A e B)
	- fetch apenas de intruções do tipo R e Imm no pipeline B
	- forwarding do pipeline A para A (A-\>A)
	- forwarding do pipeline B para B (B-\>B)
	- forwarding do pipeline B para A (B-\>A)
	- forwarding do pipeline A para B (A-\>B)
	- JAL nao causa mais bolhas
	- verificado pelos três benchmarks
	- verificado na primer25k
	- torvs6p1.sv adiciona LUI e AUIPC no pipeline B
    - torvs6p2.sv adiciona LUI, AUIPC e STOREs no pipeline B
    - torvs6p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A
    - torvs6p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A
    - torvs6p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A


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
	- verificado na primer25k
	- torvs7p1.sv adiciona LUI e AUIPC no pipeline B
    - torvs7p2.sv adiciona LUI, AUIPC e STOREs no pipeline B
    - torvs7p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A
    - torvs7p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A
    - torvs7p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A


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
	- verificado na primer25k
	- torvs8p1.sv adiciona LUI e AUIPC no pipeline B
	- torvs8p2.sv adiciona LUI, AUIPC e STOREs no pipeline B
	- torvs8p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A
	- torvs8p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A
	- torvs8p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A


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
	- verificado na primer25k
	- torvs9p1.sv adiciona LUI e AUIPC no pipeline B (primer25k check)
	- torvs9p2.sv adiciona LUI, AUIPC e STOREs no pipeline B
	- torvs9p3.sv adiciona LUI, AUIPC e STOREs no pipeline B; e permite issue com btype no pipeline A
	- torvs9p4.sv adiciona LUI, AUIPC, STOREs e LOADs no pipeline B; e permite issue em B com Btype no pipeline A
	- torvs9p5.sv adiciona LUI, AUIPC, STOREs, LOADs e Btype no pipeline B; e permite issue em B com Btype no pipeline A

