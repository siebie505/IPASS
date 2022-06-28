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
                // The first (rising) part of the phase vibrato
                if (iterationIncrement > phaseVibratoDepth) { // If this part is finished
                    state = 1;
                    iterationDecrement = 0;
                }
                else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If the previous update was long enough ago
                    currentPhase++;
                    iterationIncrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;
            case 1 :
                // The second (falling) part of the phase vibrato
                if (iterationDecrement > phaseVibratoDepth * 2) { // If this part is finished
                    state = 2;
                    iterationIncrement = 0;
                }
                else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If the previous update was long enough ago
                    currentPhase--;
                    iterationDecrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;
            case 2 :
                // The final (rising back to the original phase) part of the phase vibrato
                if (iterationIncrement > phaseVibratoDepth) {
                    state = 0;
                    iterationIncrement = 0;
                }
                else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If the previous update was long enough ago
                    currentPhase++;
                    iterationIncrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;
        }
    }
    else {
        currentPhase = startPhase;
    }
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
    timeLastUpdate = 0;
    iterationIncrement = 0;
    iterationDecrement = 0;
}