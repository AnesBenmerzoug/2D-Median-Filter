#include <systemc.h>
#include "../include/median_filter_module.h"
#include "../include/memory_module.h"
#include "../include/median_filter_tb.h"

int sc_main(int argc, char* argv[]){

  median_filter_module* median_filter = new median_filter_module("median_filter");
  memory_module* memory = new memory_module("memory");
  median_filter_tb* testbench = new median_filter_tb("median_filter_testbench");

  median_filter->initiator_socket.bind(memory->target_socket);

  // The system clock
  sc_clock Clk("Clock", 10, SC_NS, 0.5, 10, SC_NS);

  // The system reset signal
  sc_signal<bool> Rst;

  // Start and Finish signals
  sc_signal<bool> Start;
  sc_signal<bool> Finish;

  median_filter->clk(Clk);
  median_filter->rst(Rst);
  median_filter->finish(Finish);

  memory->clk(Clk);
  memory->rst(Rst);

  testbench->clk(Clk);
  testbench->rst(Rst);
  testbench->start(Start);
  testbench->finish(Finish);

  sc_start();

  return 0;
}
