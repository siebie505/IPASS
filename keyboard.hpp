//#include <vector>
#include "hwlib.hpp"

#define numKeys 13

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {
    class keyboard {
    protected:
        std::array<hwlib::pin_in*, numKeys>& keys;
//        std::vector<hwlib::pin_in*>& keys;
        std::array<bool, numKeys> keyStates;
//        std::vector<bool> keyStates;
//        std::array<bool, numKeys> usedKeys;
//        std::vector<bool> usedKeys;
//        unsigned int keyNum;

        virtual void checkActiveKeys();
    public:
        explicit keyboard(std::array<hwlib::pin_in*, numKeys>& keys);

//        explicit keyboard(std::vector<hwlib::pin_in*>& keys) : keys(keys){}

        virtual void update() = 0;

        virtual std::array<bool, numKeys> getActiveKeys() = 0;

//        virtual std::vector<bool> getActiveKeys() = 0;

//       virtual void setKeyUsed(unsigned int& keyIndex) = 0;

//        virtual std::array<bool, numKeys> getUsedKeys() = 0;
//        virtual std::vector<bool> getUsedKeys() = 0;
    };
}

#endif /* KEYBOARD_HPP */
