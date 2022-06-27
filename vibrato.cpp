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
        hwlib::cout << "s"<< "t"<< "a"<< "t"<< "e"<< ":"<< " " << state << "\n";
        switch(state) {
            case 0 :
                if (iteratieIncrement > vibratoDepth) {
                    hwlib::cout << "!" << "\n";
                    state = 1;
                    //                    fallStartTime = hwlib::now_us();
                    iteratieDecrement = 0;
                } else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
                    hwlib::cout << "?" << "\n";
                    //                    incrementStartTime = hwlib::now_us();
                    currentFreq++;
                    iteratieIncrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;

            case 1:
                hwlib::cout << "h" << "\n";
                if (iteratieDecrement > vibratoDepth * 2) {
                    state = 2;
    //                    secondClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                }
                else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
    //                    decrementStartTime = hwlib::now_us();
                    currentFreq--;
                    iteratieDecrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;
            case 2 :
                if (iteratieIncrement > vibratoDepth) {
                    state = 0;
    //                    initialClimbStartTime = hwlib::now_us();
                    iteratieIncrement = 0;
                }
                else if (currTime - timeSinceLastUpdate > timeBetweenUpdates) {
    //                    incrementStartTime = hwlib::now_us();
                    currentFreq++;
                    iteratieIncrement++;
                    timeSinceLastUpdate = hwlib::now_us();
                }
                break;

        }

    }
    else {
        currentFreq = startFreq;
    }
    hwlib::cout << "c" << "u" << "r" << "r"<< ":" << " "  << int(currentFreq) << "\n";
    chip.setFreq(currentFreq);
}

void vibrato::setFreq(const float &freq_p) {
    startFreq = freq_p;
    currentFreq = startFreq;
    iteratieDecrement = 0;
    iteratieDecrement = 0;
    state = 0;
//    initialClimbStartTime = hwlib::now_us();
}