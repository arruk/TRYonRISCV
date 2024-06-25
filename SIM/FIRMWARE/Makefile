include ../../FIRMWARE/makefile.inc
RVASFLAGS=-march=$(ARCH) -mabi=$(ABI) 
RVCFLAGS=-I. -O2 -fno-pic -march=$(ARCH) -mabi=$(ABI) -fno-stack-protector -w -Wl,--no-relax

RAM_SIZE=6144

LIBOBJECTS=putchar.o wait.o print.o memcpy.o errno.o perf.o

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

#tentativa: so alterar o tamanho do arquivo
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
	echo $@ > ../firmware.txt
