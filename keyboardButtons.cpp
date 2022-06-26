#include "keyboardButtons.hpp"
#include "hwlib.hpp"

keyboard::keyboardButtons::keyboardButtons(std::array<hwlib::pin_in *, 13>& keys) : keys(keys), keyboard() {
    keyStates.fill(0);
//    usedKeys.fill(0);
    keyNum = 13;
}


void keyboard::keyboardButtons::checkActiveKeys() {
    std::array<bool, 13> keyStates;
    for(unsigned int i = 0; i < 13; i++) {
        hwlib::pin_in* keyPointer = keys[i];
        keyPointer->refresh();
        keyStates[i] = keyPointer->read();
    }
}

void keyboard::keyboardButtons::update() {
    //    long long currTime = hwlib::now_us();
//    switch(state) {
//        case state1:
//            if(currTime - state1StartTime > threshold) {
//                state = state2;
//                state2StartTime = hwlib::now_us();
//                state2Do.exec();
//            }
//            break;
//        case state2:
//            break;
//    }
    checkActiveKeys();
}

std::array<bool, 13> keyboard::keyboardButtons::getActiveKeys() {
    return keyStates;
}