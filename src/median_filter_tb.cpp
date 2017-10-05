#include "../include/median_filter_tb.h"

void median_filter_tb::do_testbench(){
  cout << "@" << sc_time_stamp() << " Starting simulation" << endl;
  rst.write(true);
  wait(10);
  rst.write(false);
  wait();

  // Initialize Memory with image content
  cout << "@" << sc_time_stamp() << " Reading image from file" << endl;
  BMP image;
  image.ReadFromFile("img/input.bmp");

  unsigned char img[width][height];
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      img[i][j] = image(i,j)->Red;
    }
  }
  cout << "@" << sc_time_stamp() << " Writing image to memory" << endl;
  write_image(img);
  wait();

  // Start Median Filter
  start.write(true);
  cout << "@" << sc_time_stamp() << " Median filter started" << endl;
  wait();
  start.write(false);

  cout << "@" << sc_time_stamp() << " Waiting for finish signal" << endl;

  while(finish.read() != true){
    //cout << "waiting for finish signal\n";
    wait();
  }

  cout << "@" << sc_time_stamp() << " Finish signal received" << endl;

  // Read result image from memory
  cout << "@" << sc_time_stamp() << " Reading result image from memory" << endl;
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

  cout << "@" << sc_time_stamp() << " Writing result image to file" << endl;
  image_out.WriteToFile("img/output.bmp");

  cout << "@" << sc_time_stamp() << " Stopping simulation" << endl;
  sc_stop();
}

void median_filter_tb::read_image(unsigned char img[][height]){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  trans->set_read();
  trans->set_data_length(1);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      trans->set_address(i*height+j);  // address set to positon of pixel column
      trans->set_data_ptr(&(img[j][i]));  // copy directly into img array, switched coords
      initiator_socket->transport_dbg(*trans);
    }
  }
}

void median_filter_tb::write_image(unsigned char img[][height]){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  trans->set_write();
  trans->set_data_length(1);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      trans->set_address(i*height+j);  // address set to positon of pixel column
      trans->set_data_ptr(&(img[j][i]));  // copy directly into img array, switched coords
      initiator_socket->transport_dbg(*trans);
    }
  }
}
