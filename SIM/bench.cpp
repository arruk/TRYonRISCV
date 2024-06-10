#include "VSOC.h"
#include "verilated.h"
#include "femto_elf.h"
#include <iostream>


int main(int argc, char** argv, char** env) {
   VSOC top;
   top.CLK = 0;

   Elf32Info elf;
   int elf_status;

   // Call eval() so that readmemh()/initial bocks are executed
   // before anything else.
   top.eval();

   // Main simulation loop.
   while(!Verilated::gotFinish()) {
      top.CLK = !top.CLK;
      top.eval();
   }
   return 0;
}
