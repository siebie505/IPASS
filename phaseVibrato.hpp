#include "soundchip.hpp"

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
        int iteratieIncrement = 0;
        int iteratieDecrement = 0;


//        long incrementStartTime = 0;
//        long long decrementStartTime = 0;
//        long long initialClimbStartTime = 0;
//        long long fallStartTime = 0;
//        long long secondClimbStartTime = 0;
        int state = 0;
        long long timeSinceLastUpdate = 0;
    public:
        phaseVibrato(soundchip::soundchip& chip);

        void set(const bool& phaseVibratoOn_p, const int& phaseVibratoSpeed_p, const int& phaseVibratoDepth_p);

        void setPhase(const int& phase_p);

        void update();
    };
}

#endif /* PHASEVIBRATO_HPP */
