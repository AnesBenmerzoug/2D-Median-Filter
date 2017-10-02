#include "../include/memory_module.h"

void memory_module::do_memory(){
  // Initialize memory with image content
  for(int j = 0; j < height; j++){
    for(int i = 0; i < width, i++){
      mem[i+j*height] = IMAGE[i][j];
    }
  }

  while(true){
    if(rst.read() == 1){
      // Initialize memory with image content
      for(int j = 0; j < height; j++){
        for(int i = 0; i < width, i++){
          mem[i+j*height] = IMAGE[i][j];
        }
      }
      wait();
    }
  }
}

virtual void memory_module::b_transport(tlm::generic_payload& trans, sc_time& delay){
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
