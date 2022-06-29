# AD9833 Library and synthesizer application
by Siebren Bouwhuis.\
\
This library is meant to be used with an arduino, hwlib and bmptk.
# Introduction
This library allows for easy control of a AD9833 waveform generator chip as well as using it as a synthesizer. Features include n-note polyphony, where n is the number of AD9833 chips, vibrato, phase vibrato and glissando effects, easy creation of musical "keyboards" with a maximum of 108 buttons, and four waveform shapes: sine, triangle, square and half square.
# Instructions
To use this library, connect the FSYNC pin on the AD9833 to an arduino pin and put the used pin number in the enablepin object, put the SCLK pin number in the clockpin object, and the SDATA pin in the datapin object.\
\
Additional AD9833 chips can be connected for polyphony, allowing for one note per chip. The same data and clock pins can be used for all chips, but each one will need a unique enablepin, don't forget to also create the new enablepin objects. You will also need to create an AD9833 object for each chip, as well as a synthesizer object. Finally you should put all of your synthesizer objects in the synthesizer array, and change the length of the array. \
\
You can connect buttons to the arduino pins to use as musical keyboard keys, entering the pin numbers correctly and creating additional pin objects if you use more than the default (13). You should specifiy the amount of "keys" in the numkeys.hpp file, and also add them to the keysArray. By default the pins are inverted, so you need to hook up active low buttons. If you choose to active low buttons as well you should make a pin_in_invert object for each additional button. If you want to use active high buttons, you should remove the pre-existing pin_in_invert objects and change the names in the keys array. You should also specify the master clock's frequency (not the spi clock), on the module boards this is 25MHz. \
\
In the constructor of the keyboard object you can pass a starting note, this is the note your first key will play. It needs to be a value that is in the notes.hpp file, it is easiest to just tweak the variable name that is already in there. Possible values range from noteC0 up to and including noteB8. Keep in mind that the actual maximum value is (the amount of keys you have) back from B8, so if you have 13 keys the maximum starting note will be noteB7 (13 notes back from B8). \
\
Possible Values for the setWave function are SINE, TRIANGLE, SQUARE and HALF_SQUARE. 
# Licence
Copyright (c) 2022, Siebren Bouwhuis. \
See LICENCE.txt for licence information.