LIBUVM=../../libuvm/
UBIVM=../../ubivm/
LIBCOMMON=../../libcommon/
INCLUDE_DIR=-I$(LIBUVM) -I$(UBIVM) -I$(LIBCOMMON) -I../ -I/usr/include/boost/
LIB_DIR=-L$(LIBCOMMON)
CC=gcc
CCFLAGS=-g -Wall -pedantic -fPIC
LIBS=

OBJECTS = uvm_os_trail.o

LIBDIR  = ../../lib/
LIBNAME = $(LIBDIR)libuvm_os_trail

all: $(OBJECTS)
	gcc -shared -o $(LIBNAME).so $(OBJECTS) $(LIBS) $(LIB_DIR)

%.cpp:
	../ubibind trail.bind

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $(INCLUDE_DIR) $< -o $@

clean:
	rm -f *.o $(LIBNAME).so $(OBJECTS) core uvm_os_trail.cpp
