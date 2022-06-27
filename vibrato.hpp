#include "soundchip.hpp"
#include "phaseVibrato.hpp"

#ifndef VIBRATO_HPP
#define VIBRATO_HPP


namespace effects {
    class vibrato {
    private:
        soundchip::soundchip& chip;
//        effects::phaseVibrato& phaseVibrato1;
        int iteratieIncrement = 0;
        int iteratieDecrement = 0;
        float startFreq = 1000;
        float currentFreq = 1000;
        bool vibratoOn = false;
        int vibratoSpeed = 5, vibratoDepth = 5;


        int state = 0;
//        long long initialClimbStartTime = 0;
//        long long fallStartTime = 0;
//        long long secondClimbStartTime = 0;
//        long long incrementStartTime = 0;
//        long long decrementStartTime = 0;
        long long timeSinceLastUpdate = 0;

    public:
        vibrato(soundchip::soundchip& chip);

        void setAll(const float &freq_p, const bool &vibrato_p, const int &phaseVibrato_p, const int& vibratoSpeed_p);

        void setFreq(const float& freq_p);

        void update();
    };
}

#endif /* VIBRATO_HPP */
