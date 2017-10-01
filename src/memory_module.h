#ifndef MEMORY_MODULE_H
#define MEMORY_MODULE_H

#include <systemc.h>

SC_MODULE(memory_module){
  // Inputs
  sc_in<bool> clk;
  sc_in<bool> rst;

  // Main function of the memory memory_module
  void do_memory();

  SC_CTOR(memory_module){
    SC_THREAD(do_memory);
    sensitive << clk.pos();
  }
}

#endif
