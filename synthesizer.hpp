// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file
/// \brief
/// Contains the declaration for the synthesizer class
///

#include "ADCHIP.hpp"
#include "hwlib.hpp"
#include "keyboard.hpp"
#include "numkeys.hpp"
#include "vibrato.hpp"
#include "phaseVibrato.hpp"
#include "glissando.hpp"
#include "notes.hpp"

#ifndef SYNTHESIZER_HPP
#define SYNTHESIZER_HPP

namespace synthesizer {

    // TODO: change to oscillator class, move synthesizer specific stuff to new synthesizer class, which has references to oscillators

    /// A class which controls notes, keys and effects
    class synthesizer {
    private:

        /// A soundchip to play the notes out of
        soundchip::soundchip& chip;

        /// A keyboard to control the notes played
        keyboard::keyboard& keyboard;

        /// A phase vibrato effect
        effects::phaseVibrato phaseVibrato1;

        // A vibrato effect
        effects::vibrato vibrato1;

        // A glissando effect
        effects::glissando glissando1;



        /// Wether the vibrato effect is on
        bool vibrato = false;

        /// Wether the phase vibrato effect is on
        bool phaseVibrato = false;

        /// Wether the glissando effect is on
        bool glissando = false;

        /// Wether the current note is still in glissando or it is done
        bool glissandoDone = false;

        /// Wether the current note has already been sent down the chain
        bool noteSet = false;

        /// The speed of the vibrato effect
        int vibratoSpeed = 5;

        /// The depth of the vibrato effect
        int vibratoDepth = 5;

        /// The speed of the phase vibrato effect
        int phaseVibratoSpeed = 5;

        /// The depth of the phase vibrato effect
        int phaseVibratoDepth = 5;

        /// The amount of time the glissando effect takes
        int glissandoTime = 5;

        /// The frequency of the note currently being played (-1 being no note)
        float currentNote = -1;

        /// The frequency of the previous note played (-1 being no note)
        float lastNote = -1;

        /// The frequency of the in-progress of glissando note
        float busyNote = -1;

        /// The current phase value
        int currentPhase = 0;

        /// The previous phase value
        int lastPhase = -1;

        /// An array which tells which keys are pressed
        std::array<bool, NUMKEYS> keyStates;

        /// An array which tells which keys already caused notes to play (useful for polyphony)
        std::array<bool, NUMKEYS> usedKeys;

        /// A function which sets the correct current note depending on which key is pressed
        void checkNote();

    public:

        /// A constructor which takes a soundchip to send the information to and a keyboard to control the synthesizer
        synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys);

        /// Set the phase to be output to the chip
        void setPhase(const int& phase_deg);

        /// Set the wavetype to be output to the chip (SINE, TRIANGLE, SQUARE or HALF_SQUARE)
        void setWave(const waveType& wavetype);

        /// Check which keys are pressed, send new note information, update the effects
        void update();

        /// Enable the glissando effect
        void enableGlissando(const int &glissandoTime_p);

        /// Disable the glissando effect
        void disableGlissando();

        /// Enable the vibrato effect
        void enableVibrato(const int& depth, const int& speed);

        /// Disable the vibrato effect
        void disableVibrato();

        /// Enable the phase vibrato effect
        void enablePhaseVibrato(const int& depth, const int& speed);

        /// Disable the phase vibrato effect
        void disablePhaseVibrato();

        /// Play a major scale
        void playMajor(const float& startNote = noteC5);

        /// Play a minor scale
        void playMinor(const float& startNote = noteC5);

        /// Play a chromatic scale
        void playChromatic(const float& startNote = noteC5);

        /// Play a preprogrammed sound effect
        void soundEffect();

        /// Play a random frequency
        void random();

    };
}



#endif /* SYNTHESIZER_HPP */
