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

  // Interface signals with the testbench
  sc_in<bool> start;
  sc_out<bool> finish;

  // TLM 2.0 Socket that serves as interface to the Memory Module
  tlm_utils::simple_initiator_socket<median_filter_module> initiator_socket;

  // Image Dimensions
  static const int width = 100;
  static const int height = 100;

  // Temporary array to store read pixels
  unsigned char temp[9];

  // Main function of the median filter module
  void do_median();

  // Function to read pixel value from memory
  unsigned char read_pixel(unsigned int x, unsigned int y);

  // Function to write pixel value to memory
  void write_pixel(unsigned char val, unsigned int x, unsigned int y);

  SC_CTOR(median_filter_module):initiator_socket("initiator_socket"){
    SC_THREAD(do_median);
    sensitive << clk.pos();
    reset_signal_is(rst, true);
  }

};

#endif
