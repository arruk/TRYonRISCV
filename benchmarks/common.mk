REPO_ROOT := $(abspath ../)
BUILD_ROOT ?= $(REPO_ROOT)/build

FW_BUILD := $(BUILD_ROOT)/firmware
FW_OBJ := $(FW_BUILD)/obj
FW_HEX := $(FW_BUILD)/HEX

RISCV ?= /opt/riscv32
ARCH ?= rv32i
ABI ?= ilp32

TOOLCHAIN_PREFIX ?= riscv64-unknown-elf
TOOLCHAIN_BIN := $(RISCV)/bin/$(TOOLCHAIN_PREFIX)-

RVAS := $(TOOLCHAIN_BIN)as
RVLD := $(TOOLCHAIN_BIN)ld
RVOBJDUMP := $(TOOLCHAIN_BIN)objdump
RVGCC := $(TOOLCHAIN_BIN)gcc
RVOBJCOPY := $(TOOLCHAIN_BIN)objcopy

RVLIBM := $(shell $(RVGCC) -march=$(ARCH) -mabi=$(ABI) -print-file-name=libm.a)
RVLIBGCC := $(shell $(RVGCC) -march=$(ARCH) -mabi=$(ABI) -print-libgcc-file-name)

$(FW_OBJ)/%.o: %.c Makefile $(RVGCC) | $(FW_OBJ)
	$(RVGCC) $(RVCPPFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

$(FW_OBJ)/%_asm.o: %.S Makefile $(RVAS) | $(FW_OBJ)
	$(RVAS) $(RVASFLAGS) $(RVUSERASFLAGS) -c $< -o $@
