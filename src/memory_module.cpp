#include "../include/memory_module.h"

void memory_module::do_memory(){
  wait();
}

void memory_module::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay){
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  if(adr >= sc_dt::uint64(size) || byt != 0 || len > 1 || wid < len){
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  }
  if(cmd == tlm::TLM_READ_COMMAND){
    memcpy(ptr, &mem[adr], len);
  }
  else if(cmd == tlm::TLM_WRITE_COMMAND){
    memcpy(&mem[adr], ptr, len);
  }

  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

unsigned int memory_module::transport_dbg(tlm::tlm_generic_payload& trans){
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();

  if(adr >= sc_dt::uint64(size) || byt != 0 ){
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  }

  // Calculate the number of bytes to be actually copied
  unsigned int num_bytes = (len < (width*height) - adr ) ? len : (size - adr);

  if(cmd == tlm::TLM_READ_COMMAND){
    memcpy(ptr, &mem[adr], num_bytes);
  }
  else if(cmd == tlm::TLM_WRITE_COMMAND){
    memcpy(&mem[adr], ptr, num_bytes);
  }

  return num_bytes;
}
