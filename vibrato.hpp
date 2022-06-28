// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file


#include "soundchip.hpp"
#include "phaseVibrato.hpp"

#ifndef VIBRATO_HPP
#define VIBRATO_HPP


namespace effects {


    /// A class to apply the vibrato effect
    ///
    /// A class to apply the vibrato effect to a sound, information is still sent through this class if the effect is disabled
    class vibrato {
    private:
        /// The chip to send the information to
        soundchip::soundchip& chip;

        /// How often the frequency has incremented
        int iterationIncrement = 0;

        /// How often the frequency has decremented
        int iterationDecrement = 0;\

        /// The frequency of the actual note, when the vibrato started
        float startFreq = 1000;

        /// The current frequency
        float currentFreq = 1000;

        /// Wether the vibrato is turned on
        bool vibratoOn = false;

        /// The speed and depth of the vibrato effect
        int vibratoSpeed = 5, vibratoDepth = 5;

        /// The part of the vibrato wave where it is currently
        int state = 0;

        /// How long ago the latest step in the vibrato effect was
        long long timeSinceLastUpdate = 0;

    public:
        /// A constructor which requires a soundchip to send the information to
        vibrato(soundchip::soundchip& chip);

        /// set the effect paramters, namely wether it is on, it's speed and it's depth
        void set(const bool &vibrato_p, const int &vibratoSpeed_p, const int& vibratoDepth_p);

        /// Send a new note to the effect, restarting it
        void setFreq(const float& freq_p);

        /// (Sometimes) Take the next step in the vibrato effect, depending on how much time has passed since the previous step
        void update();
    };
}

#endif /* VIBRATO_HPP */
