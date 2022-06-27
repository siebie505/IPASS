#include "keyboardButtons.hpp"
#include "hwlib.hpp"

keyboard::keyboardButtons::keyboardButtons(std::array<hwlib::pin_in *, NUMKEYS>& keys, const float& startNote_hz) : keyboard(startNote_hz), keys(keys) {
}

void keyboard::keyboardButtons::checkActiveKeys() {
    for(unsigned int i = 0; i < NUMKEYS; i++) {
        hwlib::pin_in* keyPointer = keys[i];
        keyPointer->refresh();
        keyStates[i] = keyPointer->read();
    }
}

void keyboard::keyboardButtons::update() {
    checkActiveKeys();
}

std::array<bool, NUMKEYS> keyboard::keyboardButtons::getActiveKeys() {
    return keyStates;
}
