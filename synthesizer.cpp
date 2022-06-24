#include "hwlib.hpp"
#include "synthesizer.hpp"
#include "ADCHIP.hpp"

using namespace synthesizer;

void synthesizer::synthesizer::vibrato(const int& depth, const int& speed) {
    while(true) {
        for (float currentFreq = currentNote; currentFreq < currentNote + depth; currentFreq += speed) {
            setFreq(currentFreq);
            hwlib::wait_ms(10);
        }
        for (float currentFreq = currentNote + depth; currentFreq > currentNote - depth; currentFreq -= speed) {
            setFreq(currentFreq);
            hwlib::wait_ms(10);
        }
        for (float currentFreq = currentNote - depth; currentFreq < currentNote + 1; currentFreq += speed) {
            setFreq(currentFreq);
            hwlib::wait_ms(10);
        }
    }
}


void synthesizer::synthesizer::enableGlissando(const int& glissandoTime_p, const int& glissandoCooldown_p) {
    glissandoTime = glissandoTime_p;
    glissandoCooldown = glissandoCooldown_p;
    glissando = true;
}

void synthesizer::synthesizer::disableGlissando() {
    glissando = false;
}


void synthesizer::synthesizer::soundEffect() {
    for(unsigned int i = 3000; i > 100; i -= 200) {
        setFreq(i);
    }
}

void synthesizer::synthesizer::random() {
        setFreq(((rand() % 20) * 150));
        hwlib::wait_ms(100);
}

void synthesizer::synthesizer::checkNote() {
    int currentKey = 999999;
    for(unsigned int i = 0; i < keyNum; i++) {
        if (keyStates[i] == true) {
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
    keyStates = keyboard.checkKeys();
    checkNote();

    // als er geen toets ingedrukt wordt
    if(currentNote == 0) {
        stop();
        count++;
        if (count > 1) {
            lastNote = 0;
        }
    }


    else if(currentNote == lastNote && currentNote != 0) {
        // als de toets ingehouden blijft
        play();
        count = 0;
    }

    // als er momenteel een noot gespeeld wordt, en de noot hiervoor was kort genoeg geleden, en glissando staat aan, voer dan glissando uit
    else if(currentNote != 0 && lastNote != 0 && count < glissandoCooldown && glissando == true) {
        setFreq(lastNote);
        play();

        if(lastNote < currentNote) {
            // als de nieuwe noot hoger is
            for(float slideNote = lastNote; slideNote <= currentNote; slideNote += ((currentNote - lastNote) / glissandoTime)) {
                setFreq(slideNote);
                hwlib::wait_ms(10);
            }
        }

        else if(lastNote > currentNote) {
            // als de nieuwe noot lager is
            for(float slideNote = lastNote; slideNote >= currentNote; slideNote -= ((lastNote - currentNote) / glissandoTime)) {
                setFreq(slideNote);
                hwlib::wait_ms(10);
            }
        }

        setFreq(currentNote);
        lastNote = currentNote;
        count = 0;
    }

    // als er wel een noot gespeeld wordt, maar de noot hiervoro was te lang geleden voor glissando of glissando staat uit, speel dan de noot normaal
    else if(currentNote != 0 && (lastNote == 0 || count >= glissandoCooldown || glissando == false)) {
        setFreq(currentNote);
        play();
        lastNote = currentNote;
        count = 0;
    }
}

synthesizer::synthesizer::synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys) : chip(chip), keyboard(keys) {
    // defaults
    keyStates.fill(0);
    glissando = false;
    glissandoTime = 5;
    glissandoCooldown = 35;
    currentNote = 0;
    lastNote = 0;
    count = 0;
    keyNum = 13;
}

void synthesizer::synthesizer::setFreq(const float& freq_hz) {
    chip.setFreq(freq_hz);
}

void synthesizer::synthesizer::setPhase(const int& phase_deg) {
    chip.setPhase(phase_deg);
}

void synthesizer::synthesizer::setWave(const waveType& wavetype) {
    chip.setWave(wavetype);
}

void synthesizer::synthesizer::play() {
    chip.enableOutput();
}

void synthesizer::synthesizer::stop() {
    chip.disableOutput();
}

void synthesizer::synthesizer::playCMajor() {
        play();
        setFreq(noteC5);
        hwlib::wait_ms(800);
        setFreq(noteD5);
        hwlib::wait_ms(800);
        setFreq(noteE5);
        hwlib::wait_ms(800);
        setFreq(noteF5);
        hwlib::wait_ms(800);
        setFreq(noteG5);
        hwlib::wait_ms(800);
        setFreq(noteA4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteB4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteC5 * 2);
        hwlib::wait_ms(800);
        setFreq(noteB4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteA4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteG5);
        hwlib::wait_ms(800);
        setFreq(noteF5);
        hwlib::wait_ms(800);
        setFreq(noteE5);
        hwlib::wait_ms(800);
        setFreq(noteD5);
        hwlib::wait_ms(800);
        setFreq(noteC5);
        hwlib::wait_ms(800);
        stop();
}

void synthesizer::synthesizer::playCMinor() {
        play();
        setFreq(noteC5);
        hwlib::wait_ms(800);
        setFreq(noteD5);
        hwlib::wait_ms(800);
        setFreq(noteEb5);
        hwlib::wait_ms(800);
        setFreq(noteF5);
        hwlib::wait_ms(800);
        setFreq(noteG5);
        hwlib::wait_ms(800);
        setFreq(noteAb5);
        hwlib::wait_ms(800);
        setFreq(noteBb4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteC5 * 2);
        hwlib::wait_ms(800);
        setFreq(noteBb4 * 2);
        hwlib::wait_ms(800);
        setFreq(noteAb5);
        hwlib::wait_ms(800);
        setFreq(noteG5);
        hwlib::wait_ms(800);
        setFreq(noteF5);
        hwlib::wait_ms(800);
        setFreq(noteEb5);
        hwlib::wait_ms(800);
        setFreq(noteD5);
        hwlib::wait_ms(800);
        setFreq(noteC5);
        hwlib::wait_ms(800);
        stop();
}

void synthesizer::synthesizer::playAChromatic() {
        play();
        setFreq(noteA4);
        hwlib::wait_ms(800);
        setFreq(noteBb4);
        hwlib::wait_ms(800);
        setFreq(noteB4);
        hwlib::wait_ms(800);
        setFreq(noteC5);
        hwlib::wait_ms(800);
        setFreq(noteDb5);
        hwlib::wait_ms(800);
        setFreq(noteD5);
        hwlib::wait_ms(800);
        setFreq(noteEb5);
        hwlib::wait_ms(800);
        setFreq(noteE5);
        hwlib::wait_ms(800);
        setFreq(noteF5);
        hwlib::wait_ms(800);
        setFreq(noteGb5);
        hwlib::wait_ms(800);
        setFreq(noteG5);
        hwlib::wait_ms(800);
        setFreq(noteAb5);
        hwlib::wait_ms(800);
        setFreq(noteA4 * 2);
        hwlib::wait_ms(800);
        stop();
}