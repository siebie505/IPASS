#include "glissando.hpp"
#include "vibrato.hpp"
#include "hwlib.hpp"

using namespace effects;

glissando::glissando(effects::vibrato &vibrato1) : vibrato1(vibrato1) {

}

void glissando::update() {

    long long currTime = hwlib::now_us();
//    long long timeBetweenUpdates = (1 / vibratoSpeed) / (4 * vibratoDepth);
//    int glissandoSteps;
//    if(currentNote > lastNote) {
//        glissandoSteps = currentNote - lastNote;
//    }
//    else {
//        glissandoSteps = lastNote - currentNote;
//    }
    float timeBetweenUpdates_us = (glissandoTime * 1000000) / 10;

    if(lastNote == -1 || currentNote == -1) {
        currentFreq = currentNote;
        iteration = 10;
    }
    if(glissandoDone) {
        lastNote = currentNote;
        currentFreq = currentNote;
    }
    else if(glissandoOn) {
//        hwlib::cout << int(lastNote) << "\n" << int(currentNote) << "\n";

        if(lastNote == currentNote || lastNote == -1) { // als de toets ingehouden wordt op dezelfde noot, of als er hiervoor geen knop ingedrukt was(lastnote = -1 geeft aan dat er hiervoor geen note was)
            currentFreq = currentNote;
//            iteration = 0;
            hwlib::cout << 1 << "\n";
            glissandoDone = true;
        }
        else if(iteration == 0) {
            currentFreq = lastNote;
            iteration++;
            hwlib::cout << 2 << "\n";
        }

        else if(currTime - timeSinceLastUpdate > timeBetweenUpdates_us){
            hwlib::cout << 3 << "\n";
//            hwlib::cout << int(currentNote) << "\n" << int(lastNote) << "\n" << iteration << "\n";
            if (currentNote > lastNote && iteration < 10) {
                currentFreq += (currentNote - lastNote) / 10;
                iteration++;
                timeSinceLastUpdate = hwlib::now_us();
            }
            else if(currentNote > lastNote && iteration ==  10) {
                glissandoDone = true;
            }
            else if (lastNote > currentNote && iteration < 10) {
                currentFreq -= (lastNote - currentNote) / 10;
                iteration++;
                timeSinceLastUpdate = hwlib::now_us();
            }
            else if(lastNote > currentNote && iteration == 10) {
                glissandoDone = true;
            }
        }
    }
    else {
        currentFreq = currentNote;
        iteration = 0;
    }

    hwlib::cout << "i" << iteration << "\n" << int(currentFreq) << "\n";
//    hwlib::cout <<
    vibrato1.setFreq(currentFreq);
}

void glissando::setNotes(const float& currentNote_p, const float& lastNote_p) {
    glissandoDone = false;
    currentNote = currentNote_p;
    lastNote = lastNote_p;
    timeSinceLastUpdate = 0;
    iteration = 0;
}

void glissando::set(const bool &glissandoOn_p, const int& glissandoTime_p) {
//    , int glissandoCooldown_p

    glissandoOn = glissandoOn_p;
//    glissandoCooldown = glissandoCooldown_p;
    glissandoTime = glissandoTime_p;
//    iteration = 0;

}

bool glissando::getGlissandoDone() {
    return glissandoDone;
}