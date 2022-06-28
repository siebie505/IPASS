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
    glissandoTime = glissandoTime_p;
    glissando = true;
}

void synthesizer::synthesizer::disableGlissando() {
    glissando = false;
}

void synthesizer::synthesizer::checkNote() {
    int currentKey = -1;
    for(unsigned int i = 0; i < NUMKEYS; i++) {
        if (keyStates[i] == true && usedKeys[i] == false) {
        currentKey = i;
        keyboard.setKeyUsed(i); // Tell the keyboard that this key is playing a note
        break;
        }
    }

    if(currentKey + keyboard.getStartNoteNumber() >= int(noteArray.size())) { // If the current key tries to play a note out of range
        chip.disableOutput();
        currentNote = -1;
        // error
    }
    else if(currentKey == -1) { // If no key is being pressed
        currentNote = -1;
        chip.disableOutput();
    }
    else {
        currentNote = noteArray[currentKey + keyboard.getStartNoteNumber()];
        chip.enableOutput();
    }

}

void synthesizer::synthesizer::update() {
    // Check which keys are pressed and also check which keys are already playing notes
    keyStates = keyboard.getActiveKeys();
    usedKeys = keyboard.getUsedKeys();

    // Sort out which note to play based on which keys are pressed and which are already playing notes
    checkNote();

    if(currentNote != lastNote && !noteSet) { // If a new note is being played and it has not already been set
        glissando1.setNotes(currentNote, lastNote);
        busyNote = currentNote;
        noteSet = true;

    }

    // Send all the effect parameters to the effects
    glissando1.set(glissando, glissandoTime);
    vibrato1.set(vibrato, vibratoSpeed, vibratoDepth);
    phaseVibrato1.set(phaseVibrato, phaseVibratoSpeed, phaseVibratoDepth);


    // Update all the effects
    glissando1.update();
    vibrato1.update();
    phaseVibrato1.update();

    glissandoDone = glissando1.getGlissandoDone();

    if(! glissando) { // If glissando is off
        lastNote = currentNote;
        noteSet = false;
    }
    else if(glissandoDone) { // If the glissando effect is finished
        lastNote = busyNote;
        noteSet = false;
    }

    if(lastPhase != currentPhase) { // If the phase has actually changed
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
    int wait_time = 500;
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    chip.setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex]);
    hwlib::wait_ms(wait_time);

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


void synthesizer::synthesizer::playChromatic(const float& startNote) {
    int wait_time = 500;
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    chip.setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 1]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 4]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 6]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 9]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 11]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(wait_time);
    chip.disableOutput();
}

void synthesizer::synthesizer::playMinor(const float& startNote) {
    int wait_time = 500;
    unsigned int startNoteIndex = 0;
    for(unsigned int i = 0; i < noteArray.size(); i++) {
        if(noteArray[i] == startNote) {
            startNoteIndex = i;
        }
    }
    chip.setFreq(noteArray[startNoteIndex]);
    chip.enableOutput();
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 12]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 10]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 8]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 7]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 5]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 3]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex + 2]);
    hwlib::wait_ms(wait_time);
    chip.setFreq(noteArray[startNoteIndex]);
    hwlib::wait_ms(wait_time);
    chip.disableOutput();
}