#include "glissando.hpp"
#include "vibrato.hpp"
#include "hwlib.hpp"

using namespace effects;

glissando::glissando(effects::vibrato &vibrato1) : vibrato1(vibrato1) {

}

void glissando::update() {

    long long currTime = hwlib::now_us();
    float timeBetweenUpdates_us = (glissandoTime * 1000000) / 10;

    if(lastNote == -1 || currentNote == -1) { // If there is no last note or no current note
        currentFreq = currentNote;
        iteration = 10;
    }
    if(glissandoDone) { // If the glissando effect has finished
        lastNote = currentNote;
        currentFreq = currentNote;
    }
    else if(glissandoOn) {

        if(lastNote == currentNote || lastNote == -1) { // If the current note is being held, or there is no previous note
            currentFreq = currentNote;
            glissandoDone = true;
        }
        else if(iteration == 0) { // If the glissando effect has yet to be started
            currentFreq = lastNote;
            iteration++;
        }

        else if(currTime - timeLastUpdate > timeBetweenUpdates_us){ // If the last step was long enough ago
            if (currentNote > lastNote && iteration < 10) { // If the new note is higher than the previous one and the effect is not yet finished
                currentFreq += (currentNote - lastNote) / 10;
                iteration++;
                timeLastUpdate = hwlib::now_us();
            }
            else if(currentNote > lastNote && iteration ==  10) { // If the new note is higher than the previous one and the effect is finished
                glissandoDone = true;
            }
            else if (lastNote > currentNote && iteration < 10) { // If the new note is lower than the previous one and the effect is not yet finished
                currentFreq -= (lastNote - currentNote) / 10;
                iteration++;
                timeLastUpdate = hwlib::now_us();
            }
            else if(lastNote > currentNote && iteration == 10) { // If the new note is lower than the previous one and the effect is finished
                glissandoDone = true;
            }
        }
    }
    else {
        currentFreq = currentNote;
        iteration = 0;
    }

    if(currentFreq != lastFreq) { // Only update the frequency if it has actually been altered, otherwise the vibrato effect will constantly restart
        vibrato1.setFreq(currentFreq);
    }
    lastFreq = currentFreq;
}

void glissando::setNotes(const float& currentNote_p, const float& lastNote_p) {
    glissandoDone = false;
    currentNote = currentNote_p;
    lastNote = lastNote_p;
    timeLastUpdate = 0;
    iteration = 0;
}

void glissando::set(const bool &glissandoOn_p, const int& glissandoTime_p) {
    glissandoOn = glissandoOn_p;
    glissandoTime = glissandoTime_p;

}

bool glissando::getGlissandoDone() {
    return glissandoDone;
}