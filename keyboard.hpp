#include "hwlib.hpp"

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {
    class keyboard {
    private:
        std::array<hwlib::pin_in *, 13>& keys;
//        std::array<bool, 13> keyStates;
//        std::array<bool, 13> usedKeys;
        unsigned int keyNum;
    public:
        explicit keyboard(std::array<hwlib::pin_in *, 13>& keys);

        std::array<bool, 13> checkKeys();

//        void setKeyUsed(unsigned int& keyIndex);

//        std::array<bool, 13> getUsedKeys();
    };
}


#endif /* KEYBOARD_HPP */
