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


void synthesizer::synthesizer::enableGlissando(const int& glissandoTime_p) {
//    const int& glissandoCooldown_p
    glissandoTime = glissandoTime_p;
//    glissandoCooldown = glissandoCooldown_p;
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

    if(currentKey + keyboard.getStartNoteNumber() >= int(noteArray.size())) {
        chip.disableOutput();
        currentNote = -1;
        // error
    }
    else if(currentKey == -1) {
        currentNote = -1;
        chip.disableOutput();
    }
    else {
        currentNote = noteArray[currentKey + keyboard.getStartNoteNumber()];
        chip.enableOutput();
    }

}

void synthesizer::synthesizer::update() {
    keyboard.update();
    keyStates = keyboard.getActiveKeys();
//    usedKeys = keyboard.getUsedKeys();

    checkNote();

//    hwlib::cout << int(currentNote) << "\n";
    if(currentNote != lastNote && !noteSet) {
        glissando1.setNotes(currentNote, lastNote);
        busyNote = currentNote;
        noteSet = true;

    }

    glissando1.set(glissando, glissandoTime);
//    glissandoCooldown
    vibrato1.set(vibrato, vibratoSpeed, vibratoDepth);

    phaseVibrato1.set(phaseVibrato, phaseVibratoSpeed, phaseVibratoDepth);


    glissando1.update();
    vibrato1.update();
    phaseVibrato1.update();

    glissandoDone = glissando1.getGlissandoDone();
    if(! glissando) {
        lastNote = currentNote;
        noteSet = false;
    }
    else if(glissandoDone) {
        lastNote = busyNote;
        noteSet = false;
    }

    if(lastPhase != currentPhase) {
        phaseVibrato1.setPhase(currentPhase);
    }

    lastPhase = currentPhase;
}

synthesizer::synthesizer::synthesizer(soundchip::soundchip& chip, keyboard::keyboard& keys) : chip(chip), keyboard(keys),
                                                                                              phaseVibrato1(chip),
                                                                                              vibrato1(chip),
                                                                                              glissando1(vibrato1) {
}

void synthesizer::synthesizer::setPhase(const int& phase_deg) {
    currentPhase = phase_deg;
}

void synthesizer::synthesizer::setWave(const waveType& wavetype) {
    chip.setWave(wavetype);
}

void synthesizer::synthesizer::playMajor(const float& startNote) {
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    chip.setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex]);
    hwlib::wait_ms(50);

    chip.disableOutput();
}

void synthesizer::synthesizer::soundEffect() {
    chip.enableOutput();
    for(unsigned int i = 3000; i > 100; i -= 200) {
        chip.setFreq(i);
    }
    chip.disableOutput();
}

void synthesizer::synthesizer::random() {
    chip.enableOutput();
    chip.setFreq(((rand() % 20) * 150));
    hwlib::wait_ms(100);
    chip.disableOutput();
}


void synthesizer::synthesizer::playMinor(const float& startNote) {
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    chip.setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 1]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 6]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(50);
    chip.disableOutput();
}

void synthesizer::synthesizer::playChromatic(const float& startNote) {
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(50);
    chip.setFreq(noteArray[startNoteIndex]);
    hwlib::wait_ms(50);
    chip.disableOutput();
}