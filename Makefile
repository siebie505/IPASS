#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := ADCHIP.cpp synthesizer.cpp keyboardButtons.cpp vibrato.cpp phaseVibrato.cpp glissando.cpp

# header files in this project
HEADERS := ADCHIP.hpp soundchip.hpp synthesizer.hpp keyboard.hpp pin_in_invert.hpp keyboardButtons.hpp vibrato.hpp glissando.hpp phaseVibrato.hpp numkeys.hpp notes.hpp


# other places to look for files for this project
SEARCH  := 

SERIAL_PORT_DUE   ?= COM3

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due

