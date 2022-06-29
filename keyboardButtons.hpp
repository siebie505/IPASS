// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file
/// \brief
/// Contains the declaration for the keyboardButtons class
///

#include "hwlib.hpp"
#include "keyboard.hpp"
#include "notes.hpp"

#include "numkeys.hpp"

#ifndef KEYBOARD_BUTTONS_HPP
#define KEYBOARD_BUTTONS_HPP

namespace keyboard {

    /// A concrete class based on the keyboard class, which uses simple buttons as an input method
    class keyboardButtons : public keyboard {
    private:

        /// An array of all the pins connected to buttons used as keyboard keys
        std::array<hwlib::pin_in *, NUMKEYS>& keys;

        /// A function to check which buttons are pressed
        void checkActiveKeys() override;

    public:
        /// A constructor which requires an array of input pins used as keys, and the frequency of the note corresponding to the first key (must be in notes.hpp). Remember to set the amount of keyboard keys in numkeys.hpp
        keyboardButtons(std::array<hwlib::pin_in *, NUMKEYS>& keys, const float& startNote_hz = noteC4);

        /// A function to update all the information, like which keys are pressed and which are already being used
        void update() override;

        /// A function to return which keys are pressed
        std::array<bool, NUMKEYS> getActiveKeys() override;
    };
}


#endif /* KEYBOARD_BUTTONS_HPP */
