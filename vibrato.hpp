#include "soundchip.hpp"
#include "phaseVibrato.hpp"

#ifndef VIBRATO_HPP
#define VIBRATO_HPP


namespace effects {
    class vibrato {
    private:
        effects::phaseVibrato& phaseVibrato1;
        int iteratieIncrement = 0;
        int iteratieDecrement = 0;
        float startFreq = 1000;
        float currentFreq = 1000;
        bool vibratoOn = false;
        int vibratoSpeed = 5, vibratoDepth = 5;

    public:
        vibrato(effects::phaseVibrato& phaseVibrato1);

        void setAll(const float &freq_p, const bool &vibrato_p, const bool &phaseVibrato_p, const int& vibratoSpeed_p);

        void incrementFreq(const float& increment);

        void decrementFreq(const float& increment);

        void update();
    };
}

#endif /* VIBRATO_HPP */
