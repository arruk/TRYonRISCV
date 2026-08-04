REPO_ROOT := $(abspath ../)
BUILD_ROOT ?= $(REPO_ROOT)/build

FW_BUILD := $(BUILD_ROOT)/firmware
FW_OBJ := $(FW_BUILD)/obj
FW_HEX := $(FW_BUILD)/HEX

RV_UNK ?= /opt/riscv32
ARCH ?= rv32i
ABI ?= ilp32

TOOLCHAIN_PREFIX ?= riscv64-unknown-elf
TOOLCHAIN_BIN := $(RV_UNK)/bin/$(TOOLCHAIN_PREFIX)-

RVAS := $(TOOLCHAIN_BIN)as
RVLD := $(TOOLCHAIN_BIN)ld
RVOBJDUMP := $(TOOLCHAIN_BIN)objdump
RVGCC := $(TOOLCHAIN_BIN)gcc
RVOBJCOPY := $(TOOLCHAIN_BIN)objcopy

FIRMWARE_DIR ?= $(REPO_ROOT)/firmware
FIRMWARE_WORDS := $(FIRMWARE_DIR)/tools/firmware_words

SDIR := LIB
CDIR := CRT
TDIR := TESTES
LD_SCRIPT := LS/pipeline.ld

RVCPPFLAGS := -I.
RVCFLAGS := -O2 -fno-pic -march=$(ARCH) -mabi=$(ABI) \
	-fno-stack-protector -fno-tree-loop-distribute-patterns \
	-w -Wno-implicit-int \
	-Wno-implicit-function-declaration
RVASFLAGS := -march=$(ARCH)_zicsr -mabi=$(ABI)
RVLDFLAGS := -T $(LD_SCRIPT) -m elf32lriscv -nostdlib --no-relax

# Ask GCC for the multilib selected by ARCH/ABI instead of hard-coding its version.
RVLIBM := $(shell $(RVGCC) -march=$(ARCH) -mabi=$(ABI) \
	-print-file-name=libm.a)
RVLIBGCC := $(shell $(RVGCC) -march=$(ARCH) -mabi=$(ABI) \
	-print-libgcc-file-name)

S_SRCS := $(wildcard $(SDIR)/*.S)
C_SRCS := $(wildcard $(SDIR)/*.c)
PROGRAM_SRCS := $(wildcard *.c) $(wildcard $(TDIR)/*.c)

S_OBJS := $(patsubst $(SDIR)/%.S,$(FW_OBJ)/%_asm.o,$(S_SRCS))
C_OBJS := $(patsubst $(SDIR)/%.c,$(FW_OBJ)/%.o,$(C_SRCS))
PROGRAM_OBJS := $(addprefix $(FW_OBJ)/,$(notdir $(PROGRAM_SRCS:.c=.o)))
START_OBJ := $(FW_OBJ)/start_pipeline_asm.o
LIBOBJECTS := $(S_OBJS) $(C_OBJS)
DEPS := $(C_OBJS:.o=.d) $(PROGRAM_OBJS:.o=.d)

vpath %.c . $(TDIR) $(SDIR)
vpath %.S $(SDIR) $(CDIR)

.PHONY: clean print-config
.SECONDARY:

# Keep the existing user-facing target while storing every generated file in build/.
%.pipeline.hex: $(FW_BUILD)/%.pipeline.hex
	@:

$(FW_BUILD)/%.pipeline.hex: $(FW_HEX)/%.PROGROM.hex $(FW_HEX)/%.DATARAM.hex | $(FW_BUILD) $(FW_HEX)
	cp $(FW_HEX)/$*.PROGROM.hex $(FW_HEX)/PROGROM.hex
	cp $(FW_HEX)/$*.DATARAM.hex $(FW_HEX)/DATARAM.hex
	cat $(FW_HEX)/PROGROM.hex $(FW_HEX)/DATARAM.hex > $(FW_HEX)/RAM.hex
	printf '%s\n' '$*.pipeline.hex' > $(FW_BUILD)/firmware.txt
	touch $@

$(FW_HEX)/%.PROGROM.hex: $(FW_BUILD)/%.pipeline.elf $(RVOBJCOPY) | $(FW_HEX)
	$(RVOBJCOPY) -O verilog --verilog-data-width=4 --only-section=.text --gap-fill=0 --pad-to=0x10000 "$<" "$@"
$(FW_HEX)/%.DATARAM.hex: $(FW_BUILD)/%.pipeline.elf $(RVOBJCOPY) | $(FW_HEX)
	$(RVOBJCOPY) -O verilog --verilog-data-width=4 --only-section=.data --adjust-vma=-0x10000 --gap-fill=0 --pad-to=0x10000 "$<" "$@"

$(FW_BUILD)/%.pipeline.elf: $(FW_OBJ)/%.o $(START_OBJ) $(C_OBJS) $(S_OBJS) $(LD_SCRIPT) $(RVLD) | $(FW_BUILD)
	$(RVLD) $(RVLDFLAGS) $(START_OBJ) $< $(LIBOBJECTS) $(RVLIBM) $(RVLIBGCC) -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

# VPATH lets these two rules cover programs, tests, LIB/, and CRT/ sources.
$(FW_OBJ)/%.o: %.c Makefile $(RVGCC) | $(FW_OBJ)
	$(RVGCC) $(RVCPPFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

$(FW_OBJ)/%_asm.o: %.S Makefile $(RVAS) | $(FW_OBJ)
	$(RVAS) $(RVASFLAGS) $(RVUSERASFLAGS) -c $< -o $@

$(FW_BUILD) $(FW_OBJ) $(FW_HEX):
	mkdir -p $@

print-config:
	@printf 'RVGCC=%s\nARCH=%s\nABI=%s\nBUILD_ROOT=%s\n' '$(RVGCC)' '$(ARCH)' '$(ABI)' '$(BUILD_ROOT)'

clean:
	rm -rf $(FW_BUILD)

-include $(DEPS)
