#include "hwlib.hpp"
#include "keyboard.hpp"

#define numKeys 13

#ifndef KEYBOARD_BUTTONS_HPP
#define KEYBOARD_BUTTONS_HPP

namespace keyboard {
    class keyboardButtons : public keyboard {
    private:
//        std::array<hwlib::pin_in *, numKeys>& keys;
//        std::array<bool, numKeys> keyStates;
////        std::array<bool, numKeys> usedKeys;
//        unsigned int keyNum;

        void checkActiveKeys() override;

    public:
//        explicit keyboardButtons(std::vector<hwlib::pin_in *>& keys);
        explicit keyboardButtons(std::array<hwlib::pin_in *, numKeys>& keys);

        void update() override;

        std::array<bool, numKeys> getActiveKeys() override;

//        std::vector<bool> getActiveKeys() override;

//        void setKeyUsed(unsigned int& keyIndex) override;

//        std::array<bool, numKeys> getUsedKeys() override;
    };
}


#endif /* KEYBOARD_BUTTONS_HPP */
