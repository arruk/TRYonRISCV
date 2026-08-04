include common.mk

SDIR := common
LD_SCRIPT := common/pipeline.ld

RVCPPFLAGS := -I.
RVCFLAGS := -O2 -fno-pic -march=$(ARCH) -mabi=$(ABI) \
	-fno-stack-protector -fno-tree-loop-distribute-patterns \
	-w -Wno-implicit-int \
	-Wno-implicit-function-declaration
RVASFLAGS := -march=$(ARCH)_zicsr -mabi=$(ABI)
RVLDFLAGS := -T $(LD_SCRIPT) -m elf32lriscv -nostdlib --no-relax

START_SRC := $(SDIR)/start_pipeline.S
START_OBJ := $(FW_OBJ)/start_pipeline_asm.o

S_SRCS := $(filter-out $(START_SRC),$(wildcard $(SDIR)/*.S))
C_SRCS := $(wildcard $(SDIR)/*.c)

S_OBJS := $(patsubst $(SDIR)/%.S,$(FW_OBJ)/%_asm.o,$(S_SRCS))
C_OBJS := $(patsubst $(SDIR)/%.c,$(FW_OBJ)/%.o,$(C_SRCS))
LIBOBJECTS := $(S_OBJS) $(C_OBJS)

DHRYSTONE_SRCS := dhrystone/dhry_1.c dhrystone/dhry_2.c dhrystone/stubs.c
COREMARK_SRCS := coremark/core_list_join.c coremark/core_main.c coremark/core_matrix.c coremark/core_portme.c coremark/core_state.c coremark/core_util.c
RAYSTONES_SRCS := raystones/raystones.c

vpath %.c $(SDIR) tests
vpath %.S $(SDIR)

.PHONY: clean print-config
.SECONDARY:

%.pipeline.hex: $(FW_BUILD)/%.pipeline.hex
	@:

$(FW_BUILD)/%.pipeline.hex: $(FW_HEX)/%.PROGROM.hex $(FW_HEX)/%.DATARAM.hex | $(FW_BUILD) $(FW_HEX)
	#cp $(FW_HEX)/$*.PROGROM.hex $(FW_HEX)/PROGROM.hex
	#cp $(FW_HEX)/$*.DATARAM.hex $(FW_HEX)/DATARAM.hex
	touch $@

$(FW_HEX)/%.PROGROM.hex: $(FW_BUILD)/%.pipeline.elf $(RVOBJCOPY) | $(FW_HEX)
	$(RVOBJCOPY) -O verilog --verilog-data-width=4 --only-section=.text --gap-fill=0 --pad-to=0x10000 "$<" "$@"

$(FW_HEX)/%.DATARAM.hex: $(FW_BUILD)/%.pipeline.elf $(RVOBJCOPY) | $(FW_HEX)
	$(RVOBJCOPY) -O verilog --verilog-data-width=4 --only-section=.data --adjust-vma=-0x10000 --gap-fill=0 --pad-to=0x10000 "$<" "$@"

$(FW_BUILD)/%.pipeline.elf: $(FW_OBJ)/%.o $(START_OBJ) $(C_OBJS) $(S_OBJS) $(LD_SCRIPT) $(RVLD) | $(FW_BUILD)
	$(RVLD) $(RVLDFLAGS) $(START_OBJ) $< $(LIBOBJECTS) $(RVLIBM) $(RVLIBGCC) -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

$(FW_OBJ)/dhrystone.o: $(DHRYSTONE_SRCS) $(DHRYSTONE_HDRS) $(COMMON_HDRS) Makefile $(RVGCC) | $(FW_OBJ) 
	$(RVGCC) $(RVCPPFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -Idhrystone -DTIME -DRISCV -DUSE_MYSTDLIB -nostdlib -Wl,--no-relax -r $(DHRYSTONE_SRCS) -o $@

$(FW_OBJ)/coremark.o: $(COREMARK_SRCS) $(COREMARK_HDRS) $(COMMON_HDRS) Makefile $(RVGCC) | $(FW_OBJ)
	$(RVGCC) $(RVCPPFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -Icoremark -DRISCV -DTIME -DUSE_MYSTDLIB -nostdlib -Wl,--no-relax -r $(COREMARK_SRCS) -o $@

$(FW_OBJ)/raystones.o: $(RAYSTONES_SRCS) $(COMMON_HDRS) Makefile $(RVGCC) | $(FW_OBJ)
	$(RVGCC) $(RVCPPFLAGS) $(RVCFLAGS) $(RVUSERCFLAGS) -Iraystones -c $(RAYSTONES_SRCS) -o $@

$(FW_BUILD) $(FW_OBJ) $(FW_HEX):
	mkdir -p $@

all: dhrystone.pipeline.hex coremark.pipeline.hex raystones.pipeline.hex

clean:
	rm -rf $(FW_BUILD)
