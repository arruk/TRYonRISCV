REPO_ROOT := $(abspath ../)

CORE ?= torvs7C

SIM_DIR   := $(REPO_ROOT)/sim/
RTL_DIR   := $(REPO_ROOT)/rtl/

OBJ_DIR   := ./build/$(CORE)/obj_dir

SOC_DIR    := $(RTL_DIR)/soc
COMMON_DIR := $(RTL_DIR)/common
TORVS_DIR  := $(RTL_DIR)/cores/torvs
TORV_DIR   := $(RTL_DIR)/cores/torv

ifneq ($(filter torvs%,$(CORE)),)
	CPU_TYPE    := TORVS
	CORE_FILE   := $(TORVS_DIR)/$(CORE).sv
	CONFIG_FILE := $(SIM_DIR)/configs/torvs.mk	
else ifneq ($(filter torv%,$(CORE)),)
	CPU_TYPE    := TORV
	CORE_FILE   := $(TORV_DIR)/$(CORE).v
	CONFIG_FILE := $(SIM_DIR)/configs/torv.mk	
else
	$(error Core invalido: $(CORE))
endif

include $(CONFIG_FILE)

BUILD_FLAGS := $(CPU_TYPE) BENCH $(EXTRA_DEFINES)
VERILATOR_DEFINES := -D$(CPU_TYPE) -DBENCH $(addprefix -D,$(EXTRA_DEFINES))

SOURCES := $(SOC_DIR)/soc.v $(SOC_DIR)/mem.sv $(COMMON_DIR)/clockworks.v $(COMMON_DIR)/uart_tx.v $(CORE_FILE) $(COMMON_DIR)/alu.v
CPP_SOURCES := $(SIM_DIR)/bench.cpp $(SIM_DIR)/bench_monitor.cpp

TORV_CORES  := $(basename $(notdir $(wildcard $(TORV_DIR)/*.v)))
TORVS_CORES := $(basename $(notdir $(wildcard $(TORVS_DIR)/*.sv)))

BENCHMARK ?= dhrystone
BENCH_DIR := $(REPO_ROOT)/benchmarks
BENCH_HEX_DIR := $(REPO_ROOT)/benchmarks/build/hex

DATARAM_PATH := $(BENCH_HEX_DIR)/$(BENCHMARK).DATARAM.hex
PROGROM_PATH := $(BENCH_HEX_DIR)/$(BENCHMARK).PROGROM.hex

RESULTS_DIR := results
RESULTS := $(RESULTS_DIR)/results.csv
SAVE ?= 0

.PHONY: all build run clean help benchmark

all: build run

#-DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL

build:
	mkdir -p "$(OBJ_DIR)"
	verilator $(addprefix -D,$(BUILD_FLAGS))  -Wno-fatal --Mdir "$(OBJ_DIR)" --top-module SOC --cc --exe $(CPP_SOURCES) $(SOURCES)
	$(MAKE) -C "$(OBJ_DIR)" -f VSOC.mk

benchmark:
	$(MAKE) -C "$(BENCH_DIR)" "$(BENCHMARK).pipeline.hex"

run: benchmark
	mkdir -p $(RESULTS_DIR)
	$(OBJ_DIR)/VSOC \
		+DATARAM="$(DATARAM_PATH)" +PROGROM="$(PROGROM_PATH)" \
		+RESULTS="$(abspath $(RESULTS))" +CORE="$(CORE)" +BENCHMARK="$(BENCHMARK)" +SAVE=$(SAVE)\
		+ACTIVE_PIPELINES="$(ACTIVE_PIPELINES)" +PREDICTION_MASK="$(PREDICTION_MASK)" \
		+DEFINES="$(EXTRA_DEFINES)"

print:
	mlr --icsv --opprint cat results/results.csv

clean: 
	rm -rf "./build/"

.PHONY: all-torv all-torvs all-cores

all-cores: all-torv all-torvs

all-torv:
	@set -e; for core in $(TORV_CORES); do \
		$(MAKE) all CORE=$$core; \
		done

build-all-torv:
	@set -e; for core in $(TORV_CORES); do \
		$(MAKE) build CORE=$$core; \
		done

all-torvs:
	@set -e; for core in $(TORVS_CORES); do \
		$(MAKE) all CORE=$$core; \
		done

build-all-torvs:
	@set -e; for core in $(TORVS_CORES); do \
		$(MAKE) build CORE=$$core; \
		done

BENCHMARKS := dhrystone coremark raystones

help:
	@echo "Uso:"
	@echo "  make CORE=<core> [BENCHMARK=<benchmark>] [opções]"
	@echo
	@echo "Cores TORV:"
	@ls -1 "$(TORV_DIR)"/*.v 2>/dev/null \
		| sed 's|.*/||; s|\.v$$||; s|^|  |'
	@echo
	@echo "Cores TORVS:"
	@ls -1 "$(TORVS_DIR)"/*.sv 2>/dev/null \
		| sed 's|.*/||; s|\.sv$$||; s|^|  |'
	@echo
	@echo "Configuracoeis TORVS:"
	@echo "  STORE_B=1   Store no pipeline B"
	@echo "  LOAD_B=1    Load e store no pipeline B"
	@echo "  BRANCH_B=1  Branch, load e store no pipeline B"
	@echo "  RAS=1       Habilita Return Address Stack"
	@echo
	@echo "Exemplos:"
	@echo "  make CORE=torv6"
	@echo "  make CORE=torvs7C LOAD_B=1"
	@echo "  make CORE=torvs9C BRANCH_B=1 RAS=1"
	@echo
	@echo "Benchmarks disponiveis:"
	@for benchmark in $(BENCHMARKS); do \
		echo "  $$benchmark"; \
		done
	@echo
	@echo "Exemplo:"
	@echo "  make CORE=torvs9C BENCHMARK=coremark BRANCH_B=1"
	@echo
	@echo "Configuracao dos resultados:"
	@echo "  SAVE=1      Salva os resultados no CSV (padrão)"
	@echo "  SAVE=0      Executa sem salvar os resultados"
