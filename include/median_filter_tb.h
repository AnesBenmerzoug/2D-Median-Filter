#ifndef MEDIAN_FILTER_TB_H
#define MEDIAN_FILTER_TB_H

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include "../EasyBMP/EasyBMP.h"

SC_MODULE(median_filter_tb){
  // Inputs
  sc_in<bool> clk;
  sc_out<bool> rst;

  // Testbench interface
  sc_out<bool> start;    // indicates start of operation
  sc_in<bool> finish; // indicates that operation is finished

  // TLM 2.0 Socket that serves as interface to the Memory Module
  tlm_utils::simple_initiator_socket<median_filter_tb> initiator_socket;

  // Image Dimensions
  static const int width = 100;
  static const int height = 100;

  // Main function of the testbench
  void do_testbench();

  // Function used to read image from memory
  void read_image(unsigned char img[][height]);

  SC_CTOR(median_filter_tb):initiator_socket("initiator_socket_tb"){
    SC_THREAD(do_testbench);
    sensitive << clk.pos();
  }
};

#endif
