#include "vibrato.hpp"
#include "hwlib.hpp"

using namespace effects;

vibrato::vibrato(soundchip::soundchip& chip): chip(chip) {
}

void vibrato::set(const bool &vibrato_p, const int& vibratoSpeed_p,
                              const int& vibratoDepth_p) {
    vibratoOn = vibrato_p;
    vibratoSpeed = vibratoSpeed_p;
    vibratoDepth = vibratoDepth_p;
}

void vibrato::update() {
    if(vibratoOn) {

        long long currTime = hwlib::now_us();
        long long timeBetweenUpdates = (1 / (vibratoSpeed * 1000000)) / (4 * vibratoDepth);
        switch(state) {
            case 0 :
                // The first (rising) part of the vibrato
                if (iterationIncrement > vibratoDepth) { // If this part of the vibrato is finished
                    state = 1;
                    iterationDecrement = 0;
                } else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If enough time has passed since the previous update
                    currentFreq++;
                    iterationIncrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;

            case 1:
                // The second (falling) part of the vibrato
                if (iterationDecrement > vibratoDepth * 2) { // If this part of the vibrato is finished
                    state = 2;
                    iterationIncrement = 0;
                }
                else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If enough time has passed since the previous update
                    currentFreq--;
                    iterationDecrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;
            case 2 :
                // The final (rising back to the start frequency) part of the vibrato
                if (iterationIncrement > vibratoDepth) { // If this part of the vibrato is finished
                    state = 0;
                    iterationIncrement = 0;
                }
                else if (currTime - timeLastUpdate > timeBetweenUpdates) { // If enough time has passed since the previous update
                    currentFreq++;
                    iterationIncrement++;
                    timeLastUpdate = hwlib::now_us();
                }
                break;

        }

    }
    else {
        currentFreq = startFreq;
    }
    chip.setFreq(currentFreq);
}

void vibrato::setFreq(const float &freq_p) {
    startFreq = freq_p;
    currentFreq = startFreq;
    iterationDecrement = 0;
    iterationDecrement = 0;
    state = 0;
}