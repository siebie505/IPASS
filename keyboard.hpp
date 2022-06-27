#include "hwlib.hpp"
#include "numkeys.hpp"
#include "notes.hpp"

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {
    class keyboard {
    protected:

        std::array<bool, NUMKEYS> keyStates;
//        std::array<bool, NUMKEYS> usedKeys;

        float startNote;
        int startNoteNumber;

        virtual void checkActiveKeys();
    public:
        keyboard(const float& startNote_hz) : startNote(startNote_hz) {
            for(unsigned int i = 0; i < noteArray.size(); i++) {
                if (noteArray[i] == startNote_hz) {
                    startNoteNumber = i;
                }
            }
        }

        virtual void update() = 0;

        virtual std::array<bool, NUMKEYS> getActiveKeys() = 0;

        int getStartNoteNumber() { return startNoteNumber; }

//       virtual void setKeyUsed(unsigned int& keyIndex) = 0;

//        virtual std::array<bool, NUMKEYS> getUsedKeys() = 0;

    };
}

#endif /* KEYBOARD_HPP */
