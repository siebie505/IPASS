#include "hwlib.hpp"
#include "numkeys.hpp"

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {
    class keyboard {
    protected:

        std::array<bool, NUMKEYS> keyStates;
//        std::array<bool, NUMKEYS> usedKeys;

        virtual void checkActiveKeys();
    public:
        explicit keyboard() {}

        virtual void update() = 0;

        virtual std::array<bool, NUMKEYS> getActiveKeys() = 0;

//       virtual void setKeyUsed(unsigned int& keyIndex) = 0;

//        virtual std::array<bool, NUMKEYS> getUsedKeys() = 0;

    };
}

#endif /* KEYBOARD_HPP */
