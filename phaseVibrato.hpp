#include "soundchip.hpp"
#include "vibrato.hpp"

#ifndef PHASEVIBRATO_HPP
#define PHASEVIBRATO_HPP

namespace effects {
    class phaseVibrato {
    private:
        soundchip::soundchip& chip;
        bool phaseVibratoOn = false;
        int phaseVibratoSpeed = 5;
        int phaseVibratoDepth = 5;
        int startPhase = 0;
        int currentPhase = 0;
        int iterationIncrement = 0;
        int iterationDecrement = 0;
    public:
        phaseVibrato(soundchip::soundchip& chip);

        void setAll(const int& phase_p, const bool& phaseVibratoOn_p, const int& phaseVibratoSpeed_p, const int& phaseVibratoDepth_p);

        void incrementPhase(const int& increment);

        void decrementPhase(const int& decrement);

        void update();
    };
}

#endif /* PHASEVIBRATO_HPP */
