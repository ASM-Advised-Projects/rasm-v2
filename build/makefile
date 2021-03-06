# This makefile defines all executable targets associated with the RASM.


# COMPILER & LINKER MACROS

# C++ compiler and compiler flags
CXX = gcc
CXXFLAGS = -c -std=c++11 -Wall -O0

# header search directories
include_dirs = ../lib/include
include_dirs += ../include
include_dirs += ../test/include

# set CPPFLAGS to the header directories prefixed with -I
CPPFLAGS = $(addprefix -I, $(include_dirs))

# library search directories
lib_dirs = ../lib/bin ../lib/bin/Poco/native #../lib/bin/openCV/native

# set LDFLAGS to the library directories prefixed with -L
LDFLAGS = $(addprefix -L, $(lib_dirs))

# list library names
lib_names = stdc++ cppunit periphery dlib
#lib_names += opencv_core opencv_videoio opencv_calib3d
lib_names += PocoFoundation PocoNet PocoUtil
opencv_lib_files = $(wildcard ../lib/bin/openCV/native/libopencv_*.a)
opencv_lib_names1 = $(subst ../lib/bin/openCV/native/lib,,$(opencv_lib_files))
opencv_lib_names2 = $(subst .a,,$(opencv_lib_names1))
#lib_names += $(opencv_lib_names2)

# set LDLIBS to the library names prefixed with -l
LDLIBS = $(addprefix -l, $(lib_names))


# EXECUTABLE TARGETS

prog_headers = $(wildcard ../include/rasm2/*.hpp) $(wildcard ../include/rasm2/*/*.hpp)
test_headers = $(wildcard ../test/include/test/rasm2/*.hpp) $(wildcard ../test/include/test/rasm2/*/*.hpp)

rasmtest : rasmtest.o
	$(CXX) $(LDFLAGS) $(LDLIBS) -o rasmtest.out rasmtest.o $(shell pkg-config --cflags --libs opencv)

rasmtest.o : ../src/rasmtest.cpp $(prog_headers) $(test_headers)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) ../src/rasmtest.cpp

rasmmain : rasmmain.o
	$(CXX) $(LDFLAGS) $(LDLIBS) -o rasmmain.out rasmmain.o

rasmmain.o : ../src/rasmmain.cpp $(prog_headers)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) ../src/rasmmain.cpp

#rasmshell : ../src/localshell.cpp shell/shell_client.hpp


#camcalib : ../src/camera_calibration.cpp


#sysmodel : ../src/system_modeling.cpp


# ACTION TARGETS

#.PHONY : all
#all : rasmtest rasmmain rasmshell camcalib sysmodel

.PHONY : clean
clean : mostlyclean

.PHONY : mostlyclean
mostlyclean :
	rm $(wildcard *.o)
