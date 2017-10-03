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

  // Read result image from memory
  unsigned char img[width][height];
  read_image(img);

  // Write result image to file
  BMP image_out;
  image_out.SetSize(width,height);
  for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        image_out(i,j)->Red   = img[i][j];
        image_out(i,j)->Green = img[i][j];
        image_out(i,j)->Blue  = img[i][j];
        image_out(i,j)->Alpha = 0;
      }
  }

  image_out.WriteToFile("output.bmp");

  sc_stop();
}

void median_filter_tb::read_image(unsigned char img[][height]){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  trans->set_read();
  trans->set_data_length(1);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      trans->set_address(i*height + j);  // address set to positon of pixel column
      trans->set_data_ptr( &(img[i][j]) );  // copy directly into img array, switched coords
      initiator_socket->transport_dbg(*trans);
    }
  }
}
