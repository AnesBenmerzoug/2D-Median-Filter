SYSTEMC_HOME = /usr/local/systemc-2.3.1
TARGET_ARCH = linux64
SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

EXE = main
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
EASYBMP_DIR = EasyBMP

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ += obj/EasyBMP.o
INC = $(wildcard $(INC_DIR)/*.h)

CPPFLAGS += -I$(INC_DIR) -I$(EASYBMP_DIR) -I$(SYSTEMC_INC_DIR)
CFLAGS += -Wall
LDFLAGS += -L$(SYSTEMC_LIB_DIR) -pthread
LDLIBS += -lsystemc -lm

CC = g++

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) $(SYSTEMC_LIB_DIR)/libsystemc.a
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EASYBMP_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)
