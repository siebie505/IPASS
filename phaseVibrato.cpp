#include "phaseVibrato.hpp"
#include "hwlib.hpp"

using namespace effects;

phaseVibrato::phaseVibrato(soundchip::soundchip &chip) : chip(chip) {}

void phaseVibrato::update() {
    if(phaseVibratoOn) {
        long long currTime = hwlib::now_us();
        long long timeBetweenUpdates = (1 / (phaseVibratoSpeed * 1000000)) / (4 * phaseVibratoDepth);

        switch(state) {
            case 0 :
                if (iteratieIncrement > phaseVibratoDepth) {
                    state = 0;
//                    fallStartTime = hwlib::now_us();
                    iteratieDecrement = 0;
                } else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
//                    incrementStartTime = hwlib::now_us();
                    currentPhase++;
                    iteratieIncrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;
            case 1 :
                if (iteratieDecrement > phaseVibratoDepth * 2) {
                    state = 1;
//                    secondClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                } else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
//                    decrementStartTime = hwlib::now_us();
                    currentPhase--;
                    iteratieDecrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;
            case 2 :
                if (iteratieIncrement > phaseVibratoDepth) {
                    state = 2;
//                    initialClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                }
                else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
//                    incrementStartTime = hwlib::now_us();
                    currentPhase++;
                    iteratieIncrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;
        }
    }
    else {
        currentPhase = startPhase;

        chip.setPhase(currentPhase);
    }
}

void phaseVibrato::setAll(const int& phase_p, const bool &phaseVibratoOn_p, const int &phaseVibratoSpeed_p, const int &phaseVibratoDepth_p) {
    iteratieIncrement = 0;
    iteratieDecrement = 0;
    startPhase = phase_p;
    currentPhase = startPhase;
    phaseVibratoOn = phaseVibratoOn_p;
    phaseVibratoSpeed = phaseVibratoSpeed_p;
    phaseVibratoDepth = phaseVibratoDepth_p;
    state = 0;
//    initialClimbStartTime = hwlib::now_us();
    timeSinceLastUpdate = 0;
}
