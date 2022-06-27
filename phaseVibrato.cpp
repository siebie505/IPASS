#include "phaseVibrato.hpp"

using namespace effects;

phaseVibrato::phaseVibrato(soundchip::soundchip &chip) : chip(chip) {}

void phaseVibrato::update() {

}

void phaseVibrato::setAll(const int& phase_p, const bool &phaseVibratoOn_p, const int &phaseVibratoSpeed_p, const int &phaseVibratoDepth_p) {
    iterationIncrement = 0;
    iterationDecrement = 0;
    startPhase = phase_p;
    currentPhase = startPhase;
    phaseVibratoOn = phaseVibratoOn_p;
    phaseVibratoSpeed = phaseVibratoSpeed_p;
    phaseVibratoDepth = phaseVibratoDepth_p;
}

void phaseVibrato::incrementPhase(const int &increment) {
    currentPhase += increment;
    iterationIncrement++;
}

void phaseVibrato::decrementPhase(const int &decrement) {
    currentPhase -= decrement;
    iterationDecrement--;
}