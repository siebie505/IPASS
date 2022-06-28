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
                    state = 1;
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
                    state = 2;
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
                    state = 0;
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
    }
//    hwlib::cout << currentPhase << "\n";
    chip.setPhase(currentPhase);
}

void phaseVibrato::set(const bool &phaseVibratoOn_p, const int &phaseVibratoSpeed_p, const int &phaseVibratoDepth_p) {
    phaseVibratoOn = phaseVibratoOn_p;
    phaseVibratoSpeed = phaseVibratoSpeed_p;
    phaseVibratoDepth = phaseVibratoDepth_p;

}

void phaseVibrato::setPhase(const int& phase_p) {
    startPhase = phase_p;
    currentPhase = startPhase;
    state = 0;
//    initialClimbStartTime = hwlib::now_us();
    timeSinceLastUpdate = 0;
    iteratieIncrement = 0;
    iteratieDecrement = 0;
}