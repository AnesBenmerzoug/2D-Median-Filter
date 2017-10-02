#ifndef MEMORY_MODULE_H
#define MEMORY_MODULE_H

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include <image.h>

SC_MODULE(memory_module){
  // Inputs
  sc_in<bool> clk;
  sc_in<bool> rst;

  // TLM 2.0 Socket that serves as interface to the Median Filter Module
  tlm_utils::simple_target_socket<memory_module> target_socket;

  // Image Dimensions
  static const unsigned int width = 100;
  static const unsigned int height = 100;
  static const unsigned int size = width*height;

  // Actual Memory Array
  unsigned char mem[size];

  // Main function of the memory memory_module
  void do_memory();

  // Read/Write function
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);

  SC_CTOR(memory_module):socket("target socket"){
    // Register callback for incoming b_transport method callback
    target_socket.register_b_transport(this, &memory_module::b_transport);

    SC_THREAD(do_memory);
    sensitive << clk.pos();
  }
}

#endif
