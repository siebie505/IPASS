#include "hwlib.hpp"
#include "keyboard.hpp"
#include "notes.hpp"

#include "numkeys.hpp"

#ifndef KEYBOARD_BUTTONS_HPP
#define KEYBOARD_BUTTONS_HPP

namespace keyboard {
    class keyboardButtons : public keyboard {
    private:
        std::array<hwlib::pin_in *, NUMKEYS>& keys;

        void checkActiveKeys() override;

    public:
        keyboardButtons(std::array<hwlib::pin_in *, NUMKEYS>& keys, const float& startNote_hz = noteC4);

        void update() override;

        std::array<bool, NUMKEYS> getActiveKeys() override;

//        void setKeyUsed(unsigned int& keyIndex) override;

//        std::array<bool, numKeys> getUsedKeys() override;
    };
}


#endif /* KEYBOARD_BUTTONS_HPP */
