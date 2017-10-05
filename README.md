# 2D-Median-Filter

A SystemC model of a 2D Median Filter.

### Prerequisites

In order to run the program the SystemC library has to be installed.

First of all, you have to install a few dependencies:

    $ sudo apt-get install build-essential
    $ sudo apt-get install make
    
Then, you have to download the source file:

    $ cd ~/Downloads
    $ wget "http://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.1a.tar.gz"
    
After that, you have to decompress it and create the folder where object files will be stored:
    
    $ tar -xvf systemc-2.3.1a.tar.gz
    $ cd systemc-2.3.1a.tar.gz
    $ mkdir objdir
    $ cd objdir

Before compilation you have to create the directory where you'll install the library and configure everything accordingly:

    $ sudo mkdir /usr/local/systemc-2.3.1a
    $ sudo ../configure -prefix=/usr/local/systemc-2.3.1a
    
Finally, you compile the source code and install the library:
    
    $ sudo make
    $ sudo make install
    
### Running

In order to run the program, you first have to clone it and then compile it:

    $ git clone https://github.com/AnesBenmerzoug/2D-Median-Filter.git
    $ cd 2D-Median-Filter
    $ make
    
and then you just have to run it and check the output in the img folder:

    $ ./main
