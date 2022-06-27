#include "keyboardButtons.hpp"
#include "hwlib.hpp"

keyboard::keyboardButtons::keyboardButtons(std::array<hwlib::pin_in *, NUMKEYS>& keys) : keyboard(), keys(keys) {
}

void keyboard::keyboardButtons::checkActiveKeys() {
    for(unsigned int i = 0; i < NUMKEYS; i++) {
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

std::array<bool, NUMKEYS> keyboard::keyboardButtons::getActiveKeys() {
    return keyStates;
}
