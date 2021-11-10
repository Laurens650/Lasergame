#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source & header files in this project (main.cpp is automatically assumed)

HEADERS := decode_control.h pause_control.h pause_detector.h send.hpp encode_control.hpp Send_IR_control.hpp
SOURCES := decode_control.cpp pause_control.cpp pause_detector.cpp encode_control.cpp Send_IR_control.cpp


# other places to look for files for this project
SEARCH  := ../send_receive ../send_Franky

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
