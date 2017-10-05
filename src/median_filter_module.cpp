#include "../include/median_filter_module.h"

void median_filter_module::do_median(){

  unsigned char filtered_img[width][height];

  for(int i = 1; i < width-1; i++){
    for(int j = 1; j < height-1; j++){
      if(j == 1){
        temp[0] = read_pixel(i-1,j-1);
        temp[1] = read_pixel(i-1,j);
        temp[2] = read_pixel(i-1,j+1);
        temp[3] = read_pixel(i,j-1);
        temp[4] = read_pixel(i,j);
        temp[5] = read_pixel(i,j+1);
        temp[6] = read_pixel(i+1,j-1);
        temp[7] = read_pixel(i+1,j);
        temp[8] = read_pixel(i+1,j+1);
      }
      else{
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = read_pixel(i-1,j+1);
        temp[3] = temp[4];
        temp[4] = temp[5];
        temp[5] = read_pixel(i,j+1);
        temp[6] = temp[7];
        temp[7] = temp[8];
        temp[8] = read_pixel(i+1,j+1);
      }
      wait();

      std::copy(temp, temp+9, temp_sort);

      int index;
      unsigned char val;

      for(int k = 0; k < 5; k++){
        index = k;
        for(int l = k+1; l < 9; l++){
          if(temp_sort[l] < temp_sort[index])
            index = l;
        }
        val = temp_sort[k];
        temp_sort[k] = temp_sort[index];
        temp_sort[index] = val;
      }
      filtered_img[i][j] = temp_sort[4];
      wait();
    }
  }
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      write_pixel(filtered_img[i][j], i, j);
    }
  }
  finish.write(true);
  wait();
}

unsigned char median_filter_module::read_pixel(unsigned int x, unsigned int y){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  unsigned char data = 255;
  trans->set_command(tlm::TLM_READ_COMMAND);
  trans->set_address(x*width+y);
  trans->set_data_ptr(&data);
  trans->set_data_length(1);
  trans->set_streaming_width(1);
  trans->set_byte_enable_ptr(0);
  trans->set_dmi_allowed(false);
  trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  initiator_socket->b_transport(*trans, delay);

  //cout << "data read from address: " << x << ", " << y << " is " << int(data) << "\n";

  wait(delay);

  return data;
}

void median_filter_module::write_pixel(unsigned char val, unsigned int x, unsigned int y){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  trans->set_command(tlm::TLM_WRITE_COMMAND);
  trans->set_address(x*width+y);
  trans->set_data_ptr(&val);
  trans->set_data_length(1);
  trans->set_streaming_width(1);
  trans->set_byte_enable_ptr(0);
  trans->set_dmi_allowed(false);
  trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  //cout << "data written to address: " << x << ", " << y << " is " << int(val) << "\n";

  initiator_socket->b_transport(*trans, delay);

  wait(delay);
}
