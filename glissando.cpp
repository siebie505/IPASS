#include "glissando.hpp"
#include "vibrato.hpp"

using namespace effects;

glissando::glissando(effects::vibrato &vibrato1) : vibrato1(vibrato1) {

}

void glissando::update() {
    long long currTime = hwlib::now_us();
//    long long timeBetweenUpdates = (1 / vibratoSpeed) / (4 * vibratoDepth);
    long long timeBetweenUpdates_us = glissandoTime / 1000000000;

    if(glissandoOn) {
        currentFreq = lastNote;

        if(lastNote == currentNote || lastNote == -1) { // als de toets ingehouden wordt op dezelfde noot, of als er hiervoor geen knop ingedrukt was(lastnote = -1 geeft aan dat er hiervoor geen note was)
            currentFreq = currentNote;
            iteration = 0;
        }
        else if(iteration == 0) {
            iteration++;
        }
        else if(currTime - timeSinceLastUpdate > timeBetweenUpdates_us){
            if (currentNote > lastNote && iteration < currentNote - lastNote) {
                currentFreq += ((currentNote - lastNote) / 1000);
                iteration++;
            } else if (lastNote > currentNote && iteration < lastNote - currentNote) {
                currentFreq-= ((lastNote - currentNote) / 1000);
                iteration++;
            }
        }
    }
    else {
        currentFreq = currentNote;
        iteration = 0;
    }
    timeSinceLastUpdate = hwlib::now_us();
    vibrato1.setFreq(currentFreq);
}

void glissando::setAll(const float& currentNote_p, const float& lastNote_p, const bool &glissandoOn_p, const int& glissandoTime_p) {
//    , int glissandoCooldown_p
    currentNote = currentNote_p;
    lastNote = lastNote_p;
    glissandoOn = glissandoOn_p;
//    glissandoCooldown = glissandoCooldown_p;
    glissandoTime = glissandoTime_p;
    iteration = 0;
    timeSinceLastUpdate = 0;
}