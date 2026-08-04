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
	CPU_TYPE := TORVS
	CORE_FILE := $(TORVS_DIR)/$(CORE).sv
else ifneq ($(filter torv%,$(CORE)),)
	CPU_TYPE := TORV
	CORE_FILE := $(TORV_DIR)/$(CORE).v
else
	$(error Core invalido: $(CORE))
endif

SOURCES := $(SOC_DIR)/soc.v $(SOC_DIR)/mem.sv $(COMMON_DIR)/clockworks.v $(COMMON_DIR)/uart_tx.v $(CORE_FILE) $(COMMON_DIR)/alu.v

TORV_CORES  := $(basename $(notdir $(wildcard $(TORV_DIR)/*.v)))
TORVS_CORES := $(basename $(notdir $(wildcard $(TORVS_DIR)/*.sv)))

.PHONY: all build run clean help

all: build run

build:
	mkdir -p "$(OBJ_DIR)"
	verilator "-D$(CPU_TYPE)" -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal --Mdir "$(OBJ_DIR)" --top-module SOC --cc --exe "$(SIM_DIR)/bench.cpp" $(SOURCES)
	$(MAKE) -C "$(OBJ_DIR)" -f VSOC.mk

run:
	$(OBJ_DIR)/VSOC

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

help:
	@echo "Uso: make CORE=<core>"
	@echo
	@echo "Cores TORV disponíveis:"
	@ls -1 "$(TORV_DIR)"/*.v 2>/dev/null \
		| sed 's|.*/||; s|\.v$$||; s|^|  |'
	@echo
	@echo "Cores TORVS disponíveis:"
	@ls -1 "$(TORVS_DIR)"/*.sv 2>/dev/null \
		| sed 's|.*/||; s|\.sv$$||; s|^|  |'
