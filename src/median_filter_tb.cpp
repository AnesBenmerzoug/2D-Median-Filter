#include "../include/median_filter_tb.h"

void median_filter_tb::do_testbench(){
  rst.write(true);
  wait(10);
  rst.write(false);
  wait();
  start.write(true);
  cout << "median filter started\n";
  wait();
  start.write(false);

  cout << "waiting for finish signal\n";

  while(finish.read() != true){
    //cout << "waiting for finish signal\n";
    wait();
  }

  cout << "finish signal received\n";

  sc_stop();
}
