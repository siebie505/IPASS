#include "hwlib.hpp"
#include "synthesizer.hpp"

void synthesizer::synthesizer::enableVibrato(const int& depth, const int& speed) {
    vibrato = true;
    vibratoDepth = depth;
    vibratoSpeed = speed;
}

void synthesizer::synthesizer::disableVibrato() {
    vibrato = false;
}


void synthesizer::synthesizer::enablePhaseVibrato(const int& depth, const int& speed) {
    phaseVibrato = true;
    phaseVibratoDepth = depth;
    phaseVibratoSpeed = speed;
}

void synthesizer::synthesizer::disablePhaseVibrato() {
    phaseVibrato = false;
}


void synthesizer::synthesizer::enableGlissando(const int& glissandoTime_p, const int& glissandoCooldown_p) {
    glissandoTime = glissandoTime_p;
    glissandoCooldown = glissandoCooldown_p;
    glissando = true;
}

void synthesizer::synthesizer::disableGlissando() {
    glissando = false;
}

void synthesizer::synthesizer::checkNote() {
    int currentKey = -1;
    for(unsigned int i = 0; i < NUMKEYS; i++) {
        if (keyStates[i] == true ) {
//            if (keyStates[i] == true && usedKeys[i] == false) {
            currentKey = i;
        }
    }

    switch(currentKey) {
        case 0 :
            currentNote = noteC5;
            break;
        case 1 :
            currentNote = noteDb5;
            break;
        case 2 :
            currentNote = noteD5;
            break;
        case 3 :
            currentNote = noteEb5;
            break;
        case 4 :
            currentNote = noteE5;
            break;
        case 5 :
            currentNote = noteF5;
            break;
        case 6 :
            currentNote = noteGb5;
            break;
        case 7 :
            currentNote = noteG5;
            break;
        case 8 :
            currentNote = noteAb5;
            break;
        case 9 :
            currentNote = noteA4 * 2; // octaaf hoger dan A4
            break;
        case 10 :
            currentNote = noteBb4 * 2; // octaaf hoger dan Bb4
            break;
        case 11 :
            currentNote = noteB4 * 2; // octaaf hoger dan B4
            break;
        case 12 :
            currentNote = noteC5 * 2; // octaaf hoger dan C5
            break;
        default:
            currentNote = 0;
            break;
    }
}

void synthesizer::synthesizer::update() {
//    long long currTime = hwlib::now_us();
//    switch(state) {
//        case state1:
//            if(currTime - state1StartTime > threshold) {
//                state = state2;
//                state2StartTime = hwlib::now_us();
//                state2Do.exec();
//            }
//            break;
//        case state2:
//            break;
//    }

    keyboard.update();
    keyStates = keyboard.getActiveKeys();
//    usedKeys = keyboard.getUsedKeys();

    checkNote();

    vibrato1.setAll(currentNote, vibrato, vibratoSpeed, vibratoDepth);

    phaseVibrato1.setAll(currentPhase, phaseVibrato, phaseVibratoSpeed, phaseVibratoDepth);

    glissando1.setAll(currentNote, lastNote, glissando, glissandoTime, glissandoCooldown);


    vibrato1.update();
    phaseVibrato1.update();
    glissando1.update();
}

synthesizer::synthesizer::synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys) : chip(chip), keyboard(keys), phaseVibrato1(chip), vibrato1(phaseVibrato1), glissando1(phaseVibrato1) {
}

void synthesizer::synthesizer::setPhase(const int& phase_deg) {
    currentPhase = phase_deg;
}

void synthesizer::synthesizer::setWave(const waveType& wavetype) {
    chip.setWave(wavetype);
}

