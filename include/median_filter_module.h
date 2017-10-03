#ifndef MEDIAN_FILTER_MODULE_H
#define MEDIAN_FILTER_MODULE_H

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

SC_MODULE(median_filter_module){
  // Inputs
  sc_in<bool> clk;
  sc_in<bool> rst;

  // TLM 2.0 Socket that serves as interface to the Memory Module
  tlm_utils::simple_initiator_socket<median_filter_module> initiator_socket;

  // Image Dimensions
  static const unsigned int width = 100;
  static const unsigned int height = 100;

  // Main function of the median filter module
  void do_median();

  // Function to read pixel value from memory
  unsigned char read_pixel(unsigned int x, unsigned int y);

  // Function to write pixel value to memory
  void write_pixel(unsigned char val, unsigned int x, unsigned int y);

  SC_CTOR(median_filter_module):initiator_socket("initiator_socket"){
    SC_THREAD(do_median);
    sensitive << clk.pos();
  }

};

#endif
