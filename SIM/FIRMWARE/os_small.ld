MEMORY {
   PROGROM (RX) : ORIGIN = 0x30000, LENGTH = 0x08000  /* 64kB ROM */
   DATARAM (RW) : ORIGIN = 0x38000, LENGTH = 0x08000  /* 64kB RAM */   
}

SECTIONS {

    .text : {
        . = ALIGN(4);
	os_small_crt0.o (.text)
        *(.text*)
    } > PROGROM

    .data : {
	. = ALIGN(4);
        *(.data*)          
        *(.sdata*)
        *(.rodata*) 
        *(.srodata*)
        *(.bss*)
        *(.sbss*)
	
        *(COMMON)
        *(.eh_frame)  
        *(.eh_frame_hdr)
        *(.init_array*)         
        *(.gcc_except_table*)  
    } > DATARAM
}
