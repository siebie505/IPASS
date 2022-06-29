// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file
/// \brief
/// Contains the declaration for the keyboard class
///

#include "hwlib.hpp"
#include "numkeys.hpp"
#include "notes.hpp"

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace keyboard {

    /// An abstract base class which can be inherited from, used for all sorts of input methods to act as musical keyboards. Make sure to set the proper number of keys in numkeys.hpp
    class keyboard {
    protected:

        /// An array which keeps track of which keys are pressed
        std::array<bool, NUMKEYS> keyStates;

        /// An array which keeps track of which keys have already been handled, and for which a sound is already playing (used for polyphony)
        std::array<bool, NUMKEYS> usedKeys;

        /// The frequency of the note which the first key of the keyboard should play
        float startNote;

        /// The index of the startNote value in the array located in notes.hpp
        int startNoteNumber;

        /// A function that will check which keys are currently pressed
        virtual void checkActiveKeys() = 0;
    public:
        /// A constructor that only needs the frequency for the note which belongs to the first key of the keyboard (chosen frequency should be in the notes.hpp file)
        keyboard(const float& startNote_hz = noteC4) : startNote(startNote_hz) {
            for(unsigned int i = 0; i < noteArray.size(); i++) {
                if (noteArray[i] == startNote_hz) {
                    startNoteNumber = i;
                }
            }
        }

        /// A function to renew all values, like which keys are pressed and which keys have already triggered a note
        virtual void update() = 0;

        /// A function that will return an array of booleans to tell which keys are being pressed
        virtual std::array<bool, NUMKEYS> getActiveKeys() = 0;

        /// A function that will return the index of the startNote in the notes array in notes.hpp
        int getStartNoteNumber() { return startNoteNumber; }

        /// A function that will set a specific key to used, so that another oscillator will not try to use it
        virtual void setKeyUsed(unsigned int& keyIndex) { usedKeys[keyIndex] = true;}

        /// A function that will return which keys have already triggered a note
        virtual std::array<bool, NUMKEYS> getUsedKeys() { return usedKeys;}

    };
}

#endif /* KEYBOARD_HPP */
