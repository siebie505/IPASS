#include "ADCHIP.hpp"
#include "hwlib.hpp"
#include "keyboard.hpp"
#include "vector"
#include "numkeys.hpp"

#ifndef SYNTHESIZER_HPP
#define SYNTHESIZER_HPP

namespace synthesizer {
    class synthesizer {
    private:
        soundchip::soundchip& chip;
        keyboard::keyboard& keyboard;

        effects::vibrato& vibrato1;
        effects::phaseVibrato& phaseVibrato1;
        effects::glissando& glissando1;

        const float noteA4 = 440.0;
        const float noteBb4 = 466.2;
        const float noteB4 = 493.9;
        const float noteC5 = 523.3;
        const float noteDb5 = 554.4;
        const float noteD5 = 587.3;
        const float noteEb5 = 622.3;
        const float noteE5 = 659.3;
        const float noteF5 = 698.5;
        const float noteGb5 = 740.0;
        const float noteG5 = 784.0;
        const float noteAb5 = 830.6;

        bool vibrato = false;
        bool phaseVibrato = false;
        bool glissando = false;
        int vibratoSpeed = 5;
        int vibratoDepth = 5;
        int phaseVibratoSpeed = 5;
        int phaseVibratoDepth = 5;
        int glissandoTime = 5;
        int glissandoCooldown = 5;
        float currentNote = 1000;
        float lastNote = 1000;
        int currentPhase = 0;

        std::array<bool, numKeys> keyStates;

//        std::array<bool, numKeys> usedKeys;

        void checkNote();

    public:
        synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys);

        void setPhase(const int& phase_deg);

        void setWave(const waveType& wavetype);

        void update();

        void enableGlissando(const int &glissandoTime_p, const int &glissandoCooldown_p);

        void disableGlissando();

        void enableVibrato(const int& depth, const int& speed);

        void disableVibrato();

        void enablePhaseVibrato(const int& depth, const int& speed);

        void disablePhaseVibrato();

    };
}



#endif /* SYNTHESIZER_HPP */
