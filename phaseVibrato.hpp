// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file



#include "soundchip.hpp"

#ifndef PHASEVIBRATO_HPP
#define PHASEVIBRATO_HPP

namespace effects {

    /// A class to apply the phase vibrato effect
    ///
    /// A class to apply the phase vibrato effect to a sound, phase information will still pass through this class if the effect is turned off

    class phaseVibrato {
    private:

        /// A soundchip to next send the information to
        soundchip::soundchip& chip;

        /// Wether the effect is turned on
        bool phaseVibratoOn = false;

        /// The speed of the phase vibrato effect
        int phaseVibratoSpeed = 5;

        /// The depth of the phase vibrato effect
        int phaseVibratoDepth = 5;

        /// The variable which holds the phase value where it started before the effect
        int startPhase = 0;

        /// The current value of the phase
        int currentPhase = 0;

        /// How often the phase has already incremented
        int iteratieIncrement = 0;

        /// How often the phase has already decremented
        int iteratieDecrement = 0;

        /// The current part of the modulation
        int state = 0;

        /// How much time has passed since the latest increment or decrement
        long long timeSinceLastUpdate = 0;
    public:
        /// A constructor which requires a soundchip
        phaseVibrato(soundchip::soundchip& chip);

        /// A function to set the effect parameters, namely wether it is on, it's speed and it's depth
        void set(const bool& phaseVibratoOn_p, const int& phaseVibratoSpeed_p, const int& phaseVibratoDepth_p);

        /// A function to call when a new note is played, to update the current phase and to restart the effect
        void setPhase(const int& phase_p);

        /// A function that will (sometimes) do the next increase or decrease in phase, but only when enough time has passed since the last one
        void update();
    };
}

#endif /* PHASEVIBRATO_HPP */
