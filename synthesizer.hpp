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
    class synthesizer {
    private:
        soundchip::soundchip& chip;
        keyboard::keyboard& keyboard;

        effects::phaseVibrato phaseVibrato1;
        effects::vibrato vibrato1;
        effects::glissando glissando1;




        bool vibrato = false;
        bool phaseVibrato = false;
        bool glissando = false;
        bool glissandoDone = false;
        bool noteSet = false;
        int vibratoSpeed = 5;
        int vibratoDepth = 5;
        int phaseVibratoSpeed = 5;
        int phaseVibratoDepth = 5;
        int glissandoTime = 5;
//        int glissandoCooldown = 5;
        float currentNote = -1;
        float lastNote = -1;
        float busyNote = -1;
        int currentPhase = 0;
        int lastPhase = -1;

        std::array<bool, NUMKEYS> keyStates;

//        std::array<bool, NUMKEYS> usedKeys;

        void checkNote();

    public:
        synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys);

        void setPhase(const int& phase_deg);

        void setWave(const waveType& wavetype);

        void update();

        void enableGlissando(const int &glissandoTime_p);
//        , const int &glissandoCooldown_p

        void disableGlissando();

        void enableVibrato(const int& depth, const int& speed);

        void disableVibrato();

        void enablePhaseVibrato(const int& depth, const int& speed);

        void disablePhaseVibrato();

        void playMajor(const float& startNote = noteC5);
        void playMinor(const float& startNote = noteC5);
        void playChromatic(const float& startNote = noteC5);
        void soundEffect();
        void random();

    };
}



#endif /* SYNTHESIZER_HPP */
