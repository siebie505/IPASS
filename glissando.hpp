// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file
/// \brief
/// Contains the declaration for the glissando class
///

#include "vibrato.hpp"
#include "phaseVibrato.hpp"
#include "soundchip.hpp"

#ifndef GLISSANDO_HPP
#define GLISSANDO_HPP

namespace effects {

    /// \brief
    /// A class to apply the glissando effect
    /// \details
    /// A class to apply the glissando effect to a sound, if glissando is turned off information will still pass through this class, unaltered
    ///

    class glissando {
    private:

        /// The class passes the altered frequency information to the vibrato class, where it can be altered further
        effects::vibrato& vibrato1;

        /// Keeps track of wether the glissando effect is turned on
        bool glissandoOn = false;

        /// Keeps track of when the glissando effect is finished
        bool glissandoDone = false;

        /// How fast the sliding between notes occurs
        int glissandoTime = 5;

        /// The frequency of the note to be slid to
        float currentNote = 1000;

        /// The frequency of the note to be slid from
        float lastNote = 1000;

        /// The frequency currently being played
        float currentFreq = 0;

        /// The frequency that was played right before
        float lastFreq = 0;

        /// How many times the frequency has been altered in this current slide
        int iteration = 0;

        /// When the last step in the effect occurred
        long long timeLastUpdate = 0;
    public:
        /// Glissando constructor that needs only a vibrato class to next pass the frequency information to
        glissando(effects::vibrato& vibrato1);

        /// Update the glissando class information, namely wether the effect should be on and how long the glissando's should take
        void set(const bool& glissandoOn_p, const int& glissandoTime_p);

        /// Pass a new note to the glissando class, along with the previous note. Will trigger the effect to start
        void setNotes(const float& currentNote_p, const float& lastNote_p);

        /// Return wether the current glissando is finished or not
        bool getGlissandoDone();

        /// (Sometimes) Do the next step in the glissando, sometimes it will skip, depending on how long ago the last update call was
        void update();
    };
}

#endif //* GLISSANDO_HPP */
