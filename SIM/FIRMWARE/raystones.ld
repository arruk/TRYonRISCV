MEMORY {
   PROGROM (RX) : ORIGIN = 0x10000, LENGTH = 0x08000  /* 64kB ROM */
   DATARAM (RW) : ORIGIN = 0x18000, LENGTH = 0x08000  /* 64kB RAM */   
}

SECTIONS {

    .text : {
        . = ALIGN(4);
	raystones_start.o (.text)
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
