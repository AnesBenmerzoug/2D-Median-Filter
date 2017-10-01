#ifndef MEDIAN_FILTER_MODULE_H
#define MEDIAN_FILTER_MODULE_H

#include <systemc.h>

SC_MODULE(median_filter_module){
  // Inputs
  sc_in<bool> clk;
  sc_in<bool> rst;

  // Image Dimensions
  static const unsigned int width = 100;
  static const unsigned int height = 100;

  // Main function of the median filter module
  void do_median();

  SC_CTOR(median_filter_module){
    SC_THREAD(do_median);
    sensitive << clk.pos();
  }

}

#endif
