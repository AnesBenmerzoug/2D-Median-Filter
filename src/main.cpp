#include <systemc.h>
#include "../include/median_filter_module.h"
#include "../include/memory_module.h"

int sc_main(int argc, char* argv){

  median_filter_module median_filter = new median_filter_module("median filter");
  memory_module memory = new memory_module("memory");

  median_filter.initiator_socket.bind(memory.target_socket);

  

  return 0;
}
