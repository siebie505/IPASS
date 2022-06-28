// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file

#ifndef SOUNDCHIP_HPP
#define SOUNDCHIP_HPP

enum waveType{SINE, TRIANGLE, SQUARE, HALF_SQUARE};

namespace soundchip {
    /// An abstract base class which can be inherited from
    ///
    /// Used for any concrete class which controls a soundchip
    class soundchip {
    public:
        /// An empty constructor
        soundchip() {}

        /// An abstract function to set the frequency output by the chip
        virtual void setFreq(const float& freq_hz) = 0;

        /// An abstract function to set the phase output by the chip
        virtual void setPhase(const int& phase_deg) = 0;

        /// An abstract function to set the wavetype output by the chip
        virtual void setWave(const waveType& wavetype) = 0;

        /// An abstract function to enable the output of the chip
        virtual void enableOutput() = 0;

        /// An abstract function to disable the output of the chip
        virtual void disableOutput() = 0;
    };
}

#endif /* SOUNDCHIP_HPP */
