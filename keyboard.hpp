#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {
    class keyboard {
    private:
        std::array<hwlib::pin_in *, 13>& keys;
        std::array<bool, 13> keyStates;
//        std::array<bool, 13> usedKeys;
        unsigned int keyNum;
    public:
        explicit keyboard();

        virtual void update() = 0;

        virtual std::array<bool, 13> getActiveKeys() = 0;

//       virtual void setKeyUsed(unsigned int& keyIndex) = 0;

//        virtual std::array<bool, 13> getUsedKeys() = 0;
    };
}

#endif /* KEYBOARD_HPP */
