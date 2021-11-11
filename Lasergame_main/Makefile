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

HEADERS := Display.h Fire_button.h Game_control.h hit_control.h Player_info.h schiet_control.h timer_control.h encode_control.hpp Send_IR_control.hpp send.hpp logger2.hpp init_game_control.hpp Keypad.hpp keypad_listener.hpp parameter_control.hpp Bieper.h
SOURCES := Display.cpp Fire_button.cpp Game_control.cpp hit_control.cpp schiet_control.cpp timer_control.cpp Send_IR_control.cpp encode_control.cpp decode_control.cpp pause_control.cpp pause_detector.cpp init_game_control.cpp Keypad.cpp parameter_control.cpp Bieper.cpp


# other places to look for files for this project
SEARCH  := ../send_receive ../send_Franky ../Game ../Keypad

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
