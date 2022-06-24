#include "keyboard.hpp"
#include "hwlib.hpp"

//using namespace keyboard;

keyboard::keyboard::keyboard(std::array<hwlib::pin_in *, 13>& keys) : keys(keys) {
//    keyStates.fill(0);
    keyNum = 13;
}


std::array<bool, 13> keyboard::keyboard::checkKeys() {
    std::array<bool, keyNum> keyStates;
    for(unsigned int i = 0; i < keyNum; i++) {
        hwlib::pin_in* keyPointer = keys[i];
        keyPointer->refresh();
        keyStates[i] = ! keyPointer->read();
    }
    return keyStates;
}
