#include "ADCHIP.hpp"
#include "hwlib.hpp"
#include "keyboard.hpp"

#ifndef SYNTHESIZER_HPP
#define SYNTHESIZER_HPP

namespace synthesizer {
    class synthesizer {
    private:
        soundchip::soundchip& chip;
        keyboard::keyboard& keyboard;

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

        bool glissando;
        int glissandoTime;
        int glissandoCooldown;
        float currentNote;
        float lastNote;
        int count;

        unsigned int keyNum;

        std::array<bool, 13> keyStates;

        void checkNote();

    public:
        synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys);

        void setFreq(const float& freq_hz);

        void setPhase(const int& phase_deg);

        void setWave(const waveType& wavetype);

        void play();

        void stop();

        void playCMajor();

        void playCMinor();

        void playAChromatic();

        void random();

        void update();

        void soundEffect();

        void enableGlissando(const int &glissandoTime_p = 5, const int &glissandoCooldown_p = 35);

        void disableGlissando();

        void vibrato(const int &depth, const int &speed);
    };
}



#endif /* SYNTHESIZER_HPP */
