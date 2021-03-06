#ifndef MEMORY_MODULE_H
#define MEMORY_MODULE_H

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>

SC_MODULE(memory_module){
  // Inputs
  sc_in<bool> clk;
  sc_in<bool> rst;

  // TLM 2.0 Socket that serves as interface to the Median Filter Module and to the Median Filter Testbench
  tlm_utils::simple_target_socket<memory_module> target_socket;
  tlm_utils::simple_target_socket<memory_module> target_socket_tb;

  // Image Dimensions
  static const int width = 100;
  static const int height = 100;
  static const int size = width*height;

  // Actual Memory Array
  unsigned char mem[size];

  // Main function of the memory memory_module
  void do_memory();

  // Read/Write function
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);

  // Read/Write function for the Testbench
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  SC_CTOR(memory_module):target_socket("target_socket"){
    // Register callback for incoming b_transport method callback
    target_socket.register_b_transport(this, &memory_module::b_transport);
    target_socket_tb.register_transport_dbg(this, &memory_module::transport_dbg);

    SC_THREAD(do_memory);
    sensitive << clk.pos();
    reset_signal_is(rst, true);
  }
};

#endif
