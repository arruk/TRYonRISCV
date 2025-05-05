include ../../FIRMWARE/makefile.inc
RVASFLAGS= -march=$(ARCH) -mabi=$(ABI) 
RVCFLAGS=-I. -O2 -fno-pic -march=$(ARCH) -mabi=$(ABI) -fno-stack-protector -w -Wl,--no-relax

RAM_SIZE=6144
LIB=/home/arruk/riscv/SIM/FIRMWARE/LIB

SDIR = LIB
CDIR = CRT
BDIR = BUILD

S_SRCS = $(wildcard $(SDIR)/*.S)
S_CRTS = $(wildcard $(CDIR)/*.S)
C_SRCS = $(wildcard $(SDIR)/*.c)

S_OBJS = $(S_SRCS:$(SDIR)/%.S=$(BDIR)/%_asm.o)
C_OBJS = $(C_SRCS:$(SDIR)/%.c=$(BDIR)/%.o)
S_OCRT = $(S_CRTS:$(CDIR)/start_pipeline.S=$(BDIR)/start_pipeline_asm.o)

LIBOBJECTS = $(S_OBJS) $(C_OBJS)

.PRECIOUS: %.pipeline.elf %.supervisor.pipeline.elf

# DUAL MEMORY (64 kb program ROM, 64 kb data RAM)
%.pipeline.elf: %.o $(C_OBJS) $(S_OCRT) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/pipeline.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

%.PROGROM.hex: %.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	mkdir -p ../HEX/
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0 -to_addr 0xFFFF
	cp $@ ../HEX/PROGROM.hex
	#cp $@ ../../RTL/PRIMER25k/src/PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

%.DATARAM.hex: %.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	mkdir -p ../HEX/
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x10000 -to_addr 0x1FFFF
	cp $@ ../HEX/DATARAM.hex
	#cp $@ ../../RTL/PRIMER25k/src/DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

%.pipeline.hex: %.PROGROM.hex %.DATARAM.hex
	rm -rf ../HEX/RAM.hex
	cat ../HEX/PROGROM.hex ../HEX/DATARAM.hex > ../HEX/RAM.hex
	echo $@ > ../firmware.txt

#%.pipeline.hex: os.supervisor.pipeline.hex %.PROGROM.hex %.DATARAM.hex
#	rm -rf ../RAM.hex
#	cat ../PROGROM.hex ../DATARAM.hex ../RAM_SO.hex > ../RAM.hex
#	echo $@ > ../firmware.txt

# SMALL VERSION
#%.small.pipeline.elf: %.o  $(C_OBJS) $(S_CRTS:$(CDIR)/small_pipeline.S=$(BDIR)/small_pipeline_asm.o) $(S_OBJS) $(RV_BINARIES)
#	$(RVLD) -T LS/spipeline.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
#	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list
#
#%.small.PROGROM.hex: %.small.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
#	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0 -to_addr 0x7FFF
#	cp $@ ../HEX/PROGROM.hex
#	mkdir -p ../obj_dir
#	cp $@ ../obj_dir/PROGROM.hex

#%.small.DATARAM.hex: %.small.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
#	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0x8000 -to_addr 0xFFFF
#	cp $@ ../HEX/DATARAM.hex
#	mkdir -p ../obj_dir
#	cp $@ ../obj_dir/DATARAM.hex
#
#%.small.pipeline.hex: %.small.PROGROM.hex %.small.DATARAM.hex
#	rm -rf ../HEX/RAM.hex
#	cat ../HEX/PROGROM.hex ../HEX/DATARAM.hex ../HEX/RAM_SO.hex > ../HEX/RAM.hex
#	echo $@ > ../firmware.txt

# SUPERVISOR
%.supervisor.pipeline.elf: %.o $(C_OBJS) $(S_CRTS:$(CDIR)/os_one_crt0.S=$(BDIR)/os_one_crt0_asm.o) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/os_one.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

%.supervisor.PROGROM.hex: %.supervisor.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x20000 -to_addr 0x27FFF
	cp $@ ./PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

%.supervisor.DATARAM.hex: %.supervisor.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x28000 -to_addr 0x2FFFF
	cp $@ ./DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

%.supervisor.pipeline.hex: %.supervisor.PROGROM.hex %.supervisor.DATARAM.hex
	rm -rf ../HEX/RAM_SO.hex
	cat PROGROM.hex DATARAM.hex > ../HEX/RAM_SO.hex
	echo $@ > ../firmware.txt



# RAYSTONES SMALL VERSION
raystones.os.elf: raystones.o $(C_OBJS) $(S_CRTS:$(CDIR)/raystones_start.S=$(BDIR)/raystones_start_asm.o) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/raystones.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

raystones.os.PROGROM.hex: raystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x10000 -to_addr 0x17FFF
	cp $@ ../HEX/PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

raystones.os.DATARAM.hex: raystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x18000 -to_addr 0x1FFFF
	cp $@ ../HEX/DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

raystones.os.hex: raystones.os.PROGROM.hex raystones.os.DATARAM.hex
	rm -f ../HEX/RAM_RAY.hex
	cat ../HEX/PROGROM.hex ../HEX/DATARAM.hex > ../HEX/RAM_RAY.hex

dhrystones.os.elf: dhrystones.o $(C_OBJS) $(S_CRTS:$(CDIR)/dhrystones_start.S=$(BDIR)/dhrystones_start_asm.o) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/dhrystones.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

dhrystones.os.PROGROM.hex: dhrystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0 -to_addr 0x7FFF
	cp $@ ../HEX/PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

dhrystones.os.DATARAM.hex: dhrystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0x8000 -to_addr 0xFFFF
	cp $@ ../HEX/DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

dhrystones.os.hex: dhrystones.os.PROGROM.hex dhrystones.os.DATARAM.hex
	rm -f ../HEX/RAM_DHRY.hex
	cat ../HEX/PROGROM.hex ../HEX/DATARAM.hex > ../HEX/RAM_DHRY.hex

coremark.os.elf: coremark.o $(C_OBJS) $(S_CRTS:$(CDIR)/coremark_start.S=$(BDIR)/coremark_start_asm.o) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/coremark.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

coremark.os.PROGROM.hex: coremark.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x20000 -to_addr 0x27FFF
	cp $@ ../HEX/PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

coremark.os.DATARAM.hex: coremark.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x28000 -to_addr 0x2FFFF
	cp $@ ../HEX/DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

coremark.os.hex: coremark.os.PROGROM.hex coremark.os.DATARAM.hex
	rm -f ../HEX/RAM_CM.hex
	cat ../HEX/PROGROM.hex ../HEX/DATARAM.hex > ../HEX/RAM_CM.hex

# OS SMALL VERSION
allsmall: os.small.hex dhrystones.os.hex raystones.os.hex coremark.os.hex
	rm -f ../HEX/RAM.hex
	cat ../HEX/RAM_DHRY.hex ../HEX/RAM_RAY.hex ../HEX/RAM_CM.hex ../HEX/RAM_SO.hex > ../HEX/RAM.hex
	echo "os" > ../firmware.txt
	#rm -rf ../PROGROM.hex ../DATARAM.hex ../RAM_P.hex ../RAM_SO.hex


# OS SMALL VERSION
%.small.elf: %.o $(C_OBJS) $(S_CRTS:$(CDIR)/os_small_crt0.S=$(BDIR)/os_small_crt0_asm.o) $(S_OBJS) $(RV_BINARIES)
	$(RVLD) -T LS/os_small.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

%.small.PROGROM.hex: %.small.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x40000 -max_addr 0x40000 -out $@ -from_addr 0x30000 -to_addr 0x37FFF
	cp $@ ./PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

%.small.DATARAM.hex: %.small.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x40000 -max_addr 0x40000 -out $@ -from_addr 0x38000 -to_addr 0x3FFFF
	cp $@ ./DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

%.small.hex: %.small.PROGROM.hex %.small.DATARAM.hex
	rm -rf ../HEX/RAM_SO.hex
	cat PROGROM.hex DATARAM.hex > ../HEX/RAM_SO.hex
	echo $@ > ../firmware.txt


$(BDIR)/%.o: $(SDIR)/%.c
	mkdir -p BUILD/
	$(RVGCC) $(RVCFLAGS) $(RVUSERCFLAGS) -c $< -o $@

$(BDIR)/%_asm.o: $(SDIR)/%.S $(RV_BINARIES)
	mkdir -p BUILD/
	$(RVAS) $(RVASFLAGS) $(RVUSERASFLAGS) -c $< -o $@

$(BDIR)/%_asm.o: $(CDIR)/%.S $(RV_BINARIES)
	mkdir -p BUILD/
	$(RVAS) $(RVASFLAGS) $(RVUSERASFLAGS) -c $< -o $@
