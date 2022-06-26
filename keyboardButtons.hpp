#include "hwlib.hpp"
#include "keyboard.hpp"

#ifndef KEYBOARD_BUTTONS_HPP
#define KEYBOARD_BUTTONS_HPP

namespace keyboard {
    class keyboardButtons : public keyboard {
    private:
//        std::array<hwlib::pin_in *, 13>& keys;
//        std::array<bool, 13> keyStates;
////        std::array<bool, 13> usedKeys;
//        unsigned int keyNum;

        void checkActiveKeys();

    public:
        explicit keyboardButtons(std::array<hwlib::pin_in *, 13>& keys);

        void update();

        std::array<bool, 13> getActiveKeys();

//        void setKeyUsed(unsigned int& keyIndex);

//        std::array<bool, 13> getUsedKeys();
    };
}


#endif /* KEYBOARD_BUTTONS_HPP */
