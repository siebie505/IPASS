#include "vibrato.hpp"
#include "hwlib.hpp"

using namespace effects;

vibrato::vibrato(soundchip::soundchip& chip): chip(chip) {
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
    state = 0;
//    initialClimbStartTime = hwlib::now_us();
    timeSinceLastUpdate = 0;
}

void vibrato::update() {
    if(vibratoOn) {
        long long currTime = hwlib::now_us();
        long long timeBetweenUpdates = (1 / (vibratoSpeed * 1000000)) / (4 * vibratoDepth);

        switch(state) {
            case 0 :
                if (iteratieIncrement > vibratoDepth) {
                    state = 1;
                    //                    fallStartTime = hwlib::now_us();
                    iteratieDecrement = 0;
                } else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
                    //                    incrementStartTime = hwlib::now_us();
                    currentFreq++;
                    iteratieIncrement++;
                }
                break;

            case 1:
                if (iteratieDecrement > vibratoDepth * 2) {
                    state = 2;
    //                    secondClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                }
                else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
    //                    decrementStartTime = hwlib::now_us();
                    currentFreq--;
                    iteratieDecrement++;
                }
                break;
            case 2 :
                if (iteratieIncrement > vibratoDepth) {
                    state = 0;
    //                    initialClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                } else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
    //                    incrementStartTime = hwlib::now_us();
                    currentFreq++;
                    iteratieIncrement++;
                }
                break;

        }

    }
    else {
        currentFreq = startFreq;
    }
    timeSinceLastUpdate = hwlib::now_us();
    chip.setFreq(startFreq);
}

void vibrato::setFreq(const float &freq_p) {
    startFreq = freq_p;
    currentFreq = startFreq;
    iteratieDecrement = 0;
    iteratieDecrement = 0;
    state = 0;
//    initialClimbStartTime = hwlib::now_us();
    timeSinceLastUpdate = 0;
}