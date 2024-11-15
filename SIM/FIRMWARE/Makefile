include ../../FIRMWARE/makefile.inc
RVASFLAGS= -march=$(ARCH) -mabi=$(ABI) 
RVCFLAGS=-I. -O2 -fno-pic -march=$(ARCH) -mabi=$(ABI) -fno-stack-protector -w -Wl,--no-relax

RAM_SIZE=6144

LIBOBJECTS=putchar.o wait.o print.o memcpy.o errno.o perf.o change.o csr.o halt.o

.PRECIOUS: %.pipeline.elf %.supervisor.pipeline.elf

# DUAL MEMORY (64 kb program ROM, 64 kb data RAM)
%.pipeline.elf: %.o start_pipeline.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T pipeline.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

%.PROGROM.hex: %.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0 -to_addr 0xFFFF
	cp $@ ../PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

%.DATARAM.hex: %.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x10000 -to_addr 0x1FFFF
	cp $@ ../DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

%.pipeline.hex: %.PROGROM.hex %.DATARAM.hex
	echo $@ > ../firmware.txt

#%.pipeline.hex: os.supervisor.pipeline.hex %.PROGROM.hex %.DATARAM.hex
#	rm -rf ../RAM.hex
#	cat ../PROGROM.hex ../DATARAM.hex ../RAM_SO.hex > ../RAM.hex
#	echo $@ > ../firmware.txt

# SMALL VERSION
%.small.pipeline.elf: %.o small_start.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T spipeline.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

%.small.PROGROM.hex: %.small.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0 -to_addr 0x7FFF
	cp $@ ../PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

%.small.DATARAM.hex: %.small.pipeline.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0x8000 -to_addr 0xFFFF
	cp $@ ../DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

%.small.pipeline.hex: %.small.PROGROM.hex %.small.DATARAM.hex
	rm -rf ../RAM.hex
	cat ../PROGROM.hex ../DATARAM.hex ../RAM_SO.hex > ../RAM.hex
	echo $@ > ../firmware.txt

# SUPERVISOR
%.supervisor.pipeline.elf: %.o os_one_crt0.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T os_one.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
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
	rm -rf ../RAM_SO.hex
	cat PROGROM.hex DATARAM.hex > ../RAM_SO.hex
	echo $@ > ../firmware.txt

# OS SMALL VERSION
allsmall: os.small.hex dhrystones.os.hex raystones.os.hex coremark.os.hex
	rm -f ../RAM.hex
	cat ../RAM_DHRY.hex ../RAM_RAY.hex ../RAM_CM.hex ../RAM_SO.hex > ../RAM.hex
	echo "os" > ../firmware.txt
	#rm -rf ../PROGROM.hex ../DATARAM.hex ../RAM_P.hex ../RAM_SO.hex

# RAYSTONES SMALL VERSION
raystones.os.elf: raystones.o raystones_start.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T raystones.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

raystones.os.PROGROM.hex: raystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x10000 -to_addr 0x17FFF
	cp $@ ../PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

raystones.os.DATARAM.hex: raystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x20000 -max_addr 0x20000 -out $@ -from_addr 0x18000 -to_addr 0x1FFFF
	cp $@ ../DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

raystones.os.hex: raystones.os.PROGROM.hex raystones.os.DATARAM.hex
	cat ../PROGROM.hex ../DATARAM.hex > ../RAM_RAY.hex

# DHRYSTONES SMALL VERSION
dhrystones.os.elf: dhrystones.o dhrystones_start.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T dhrystones.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

dhrystones.os.PROGROM.hex: dhrystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0 -to_addr 0x7FFF
	cp $@ ../PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

dhrystones.os.DATARAM.hex: dhrystones.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x10000 -max_addr 0x10000 -out $@ -from_addr 0x8000 -to_addr 0xFFFF
	cp $@ ../DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

dhrystones.os.hex: dhrystones.os.PROGROM.hex dhrystones.os.DATARAM.hex
	cat ../PROGROM.hex ../DATARAM.hex > ../RAM_DHRY.hex

# DHRYSTONES SMALL VERSION
coremark.os.elf: coremark.o coremark_start.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T coremark.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

coremark.os.PROGROM.hex: coremark.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x20000 -to_addr 0x27FFF
	cp $@ ../PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

coremark.os.DATARAM.hex: coremark.os.elf $(FIRMWARE_DIR)/TOOLS/firmware_words 
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x30000 -max_addr 0x30000 -out $@ -from_addr 0x28000 -to_addr 0x2FFFF
	cp $@ ../DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

coremark.os.hex: coremark.os.PROGROM.hex coremark.os.DATARAM.hex
	cat ../PROGROM.hex ../DATARAM.hex > ../RAM_CM.hex

# OS SMALL VERSION
os.small.elf: os.o os_small_crt0.o $(LIBOBJECTS) $(RV_BINARIES)
	$(RVLD) -T os_small.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
	$(RVOBJDUMP) -Mnumeric -D $@ > $@.list

os.small.PROGROM.hex: os.small.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x40000 -max_addr 0x40000 -out $@ -from_addr 0x30000 -to_addr 0x37FFF
	cp $@ ./PROGROM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/PROGROM.hex

os.small.DATARAM.hex: os.small.elf $(FIRMWARE_DIR)/TOOLS/firmware_words
	$(FIRMWARE_DIR)/TOOLS/firmware_words $< -ram 0x40000 -max_addr 0x40000 -out $@ -from_addr 0x38000 -to_addr 0x3FFFF
	cp $@ ./DATARAM.hex
	mkdir -p ../obj_dir
	cp $@ ../obj_dir/DATARAM.hex

os.small.hex: os.small.PROGROM.hex os.small.DATARAM.hex
	rm -rf ../RAM_SO.hex
	cat PROGROM.hex DATARAM.hex > ../RAM_SO.hex
	echo $@ > ../firmware.txt

