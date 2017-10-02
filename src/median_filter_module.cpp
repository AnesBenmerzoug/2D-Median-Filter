#include "../include/median_filter_module.h"

void median_filter_module::do_median(){
  
}

unsigned char read_pixel(unsigned int x, unsigned int y){
  tlm::tlm_generic_payload trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);
  unsigned char data = 0;

  trans.set_command(tlm::TLM_READ_COMMAND);
  trans.set_address(x+y*height);
  trans.set_data_ptr(&data);
  trans.set_data_length(1);
  trans.set_streaming_width(1);
  trans.set_byte_enable_ptr(0);
  trans.set_dmi_allowed(false);
  trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  initiator_socket.b_transport(&trans, delay);

  return data;
}

void write_pixel(unsigned char val, unsigned int x, unsigned int y){
  tlm::tlm_generic_payload trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);
  trans.set_command(tlm::TLM_WRITE_COMMAND);
  trans.set_address(x+y*height);
  trans.set_data_ptr(&val);
  trans.set_data_length(1);
  trans.set_streaming_width(1);
  trans.set_byte_enable_ptr(0);
  trans.set_dmi_allowed(false);
  trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  initiator_socket.b_transport(&trans, delay);
}
