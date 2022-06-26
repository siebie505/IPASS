#include "keyboardButtons.hpp"
#include "hwlib.hpp"

keyboard::keyboardButtons::keyboardButtons(std::array<hwlib::pin_in *, numKeys>& keys) : keyboard(keys) {
    keyStates.fill(0);
//    usedKeys.fill(0);
}

//keyboard::keyboardButtons::keyboardButtons(std::vector<hwlib::pin_in *>& keys) :  keyboard(keys) {
////    keyStates.fill(0);
////    usedKeys.fill(0);
//}

void keyboard::keyboardButtons::checkActiveKeys() {
//    std::array<bool, numKeys> keyStates;
    for(unsigned int i = 0; i < numKeys; i++) {
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

std::array<bool, numKeys> keyboard::keyboardButtons::getActiveKeys() {
    return keyStates;
}

//std::vector<bool> keyboard::keyboardButtons::getActiveKeys() {
//    return keyStates;
//}