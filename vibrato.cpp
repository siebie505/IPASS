#include "vibrato.hpp"

using namespace effects;

void vibrato::incrementFreq(const float& increment) {
    currentFreq += increment;
    iteratieIncrement++;
}


void vibrato::decrementFreq(const float& decrement) {
    currentFreq -= decrement;
    iteratieDecrement++;
}


vibrato::vibrato(phaseVibrato& phaseVibrato1): phaseVibrato1(phaseVibrato1) {
}

void vibrato::setAll(const float &freq_p, const bool &vibrato_p, const int& vibratoSpeed_p,
                              const int& vibratoDepth_p) {
    startFreq = freq_p;
    currentFreq = startFreq;
    vibratoOn = vibrato_p;
    vibratoSpeed = vibratoSpeed_p;
    vibratoDepth = vibratoDepth_p;
    iteratieIncrement = 0;
    iteratieDecrement = 0;
}

void vibrato::update() {

}