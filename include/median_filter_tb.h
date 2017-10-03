#ifndef MEDIAN_FILTER_TB_H
#define MEDIAN_FILTER_TB_H

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

SC_MODULE(median_filter_tb){
  // Inputs
  sc_in<bool> clk;
  sc_out<bool> rst;

  // Testbench interface
  sc_out<bool> start;    // indicates start of operation
  sc_in<bool> finish; // indicates that operation is finished

  // Image Dimensions
  static const int width = 100;
  static const int height = 100;

  // Main function of the testbench
  void do_testbench();

  SC_CTOR(median_filter_tb){
    SC_THREAD(do_testbench);
    sensitive << clk.pos();
  }
};

#endif
