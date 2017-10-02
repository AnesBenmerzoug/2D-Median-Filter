CC=g++
CFLAGS=-Wall -std=c++0x
LDFLAGS=-I/include -L$(SYSTEMC_LIB_DIR) -lsystemc
TARGET=main

all: $(TARGET)

$(TARGET): main.o median_filter_module.o memory_module.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) memory_module.o median_filter_module.o main.o

main.o: main.c median_filter_module.h memory_module.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.c

median_filter_module.o: median_filter_module.c median_filter_module.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c median_filter_module.c

memory_module.o: memory_module.c memory_module.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c memory_module.c

clean:
	rm -f *.o main Output.bmp *.cpp.*
