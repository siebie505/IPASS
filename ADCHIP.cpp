#include "hwlib.hpp"
#include "ADCHIP.hpp"

using namespace soundchip;

void ad9833::setPhase(const int& phaseDeg) {
    setPhase(phaseDeg, 0);
}

void ad9833::setFreq(const float& freqHz) {
    setFreq(freqHz, 0);
}

void ad9833::enableOutput() {
    enableOutput(0, 0);
}

ad9833::ad9833(hwlib::pin_out& enablePin_p, hwlib::pin_out& clockPin_p, hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus, const int& masterClock) :
    soundchip(), enablePin(enablePin_p), clockPin(clockPin_p), masterClock(masterClock), spi_bus(spi_bus) {
    enablePin.write(1);
    reset();
}

void ad9833::reset() {
    // defaults
    freqReg0 = 5000;
    freqReg1 = 5000;
    phaseReg0 = 0;
    phaseReg1 = 0;
    wavetype = SINE;
    dacOff = false;
    intClockOff = false;
    resetOn = true;
    choosePhaseReg1 = false;
    chooseFreqReg1 = false;


    writeControl();
    writeFreq(0);
    writePhase(0);
    writeFreq(1);
    writePhase(1);
}

void ad9833::setFreq(const float& freq, const int& registerNum) {
    if(registerNum == 0) {
        freqReg0 = freq;
        writeFreq(0);
    }
    else if(registerNum == 1) {
        freqReg1 = freq;
        writeFreq(1);
    }
    else {
        // error
    }
}

void ad9833::setPhase(const int& phase, const int& registerNum) {
    if(registerNum == 0) {
        phaseReg0 = phase;
        writePhase(0);
    }
    else if(registerNum == 1) {
        phaseReg1 = phase;
        writePhase(1);
    }
    else {
        // error
    }
}

void ad9833::setWave(const waveType& wavetype_p) {
    wavetype = wavetype_p;
    dacOff = false;
    if(wavetype_p == SQUARE || wavetype_p == HALF_SQUARE) {
        dacOff = true; // The DAC can be turned off if using a square wave
    }
    writeControl();
}

void ad9833::enableOutput(const int& freqReg, const int& phaseReg) {
    resetOn = false;
    if (freqReg == 1) {
        chooseFreqReg1 = true;
    }
    else if(freqReg == 0) {
        chooseFreqReg1 = false;
    }
    else {
        // error
    }
    if (phaseReg == 1) {
        choosePhaseReg1 = true;
    }
    else if(phaseReg == 0) {
        choosePhaseReg1 = false;
    }
    else {
        // error
    }
    writeControl();
}

void ad9833::disableOutput() {
    resetOn = true;
    writeControl();
}

void ad9833::writeControl() {
    uint16_t controlBytes = 0;
    controlBytes |= b28Bit;
    if(chooseFreqReg1 == 1) {
        controlBytes |= freqSelectBit;
    }
    if(choosePhaseReg1 == 1) {
        controlBytes |= phaseSelectBit;
    }
    if(resetOn) {
        controlBytes |= resetBit;
    }
    if(intClockOff) {
        controlBytes |= sleep1Bit;
    }
    if(dacOff) {
        controlBytes |= sleep12Bit;
    }
    switch(wavetype) {
        case SINE :
            break;
        case TRIANGLE :
            controlBytes |= modeBit;
            break;
        case SQUARE :
            controlBytes |= opbitenBit;
            controlBytes |= div2Bit;
            break;
         case HALF_SQUARE :
            controlBytes |= opbitenBit;
            break;
    }
    writeTwoBytes(controlBytes);
}

void ad9833::writeFreq(const int& registerNum) {
    uint16_t freqBytesLSB = 0;
    uint16_t freqBytesMSB = 0;
    int freqHz = 0;
    if(registerNum == 0) {
        freqBytesLSB |= freqReg0Bit;
        freqBytesMSB |= freqReg0Bit;
        freqHz = freqReg0;
    }
    else {
        freqBytesLSB |= freqReg1Bit;
        freqBytesMSB |= freqReg1Bit;
        freqHz = freqReg1;
    }

    long long freqValue = freqHz * twoPow28 / masterClock;
    freqBytesLSB |= (int(freqValue) & lsbMaskFreq);
    freqBytesMSB |= ((int(freqValue) & msbMaskFreq) >> 14);

    writeTwoBytes(freqBytesLSB);
    writeTwoBytes(freqBytesMSB);
}

void ad9833::writePhase(const int& registerNum) {
    uint16_t phaseBytes = 0;
    int phaseDeg = 0;
    if(registerNum == 0) {
        phaseBytes |= phaseReg0Bit;
        phaseDeg = phaseReg0;
    }
    else {
        phaseBytes |= phaseReg1Bit;
        phaseDeg = phaseReg1;
    }


    double slope = 1.0 / totalDegrees;
    float phaseMapped = slope * phaseDeg * 4.0; // Map the phase value from a vale in degrees (0-360) to a value the chip accepts


    int phaseValue = phaseMapped * twoPow12 / twoPi;


    phaseBytes |= (phaseValue & maskPhase);
    writeTwoBytes(phaseBytes);
}


void ad9833::writeTwoBytes(const uint16_t& data) {
    uint8_t dataLSB = data & lsbMaskControl;
    uint8_t dataMSB = (data & msbMaskControl) >> 8;
    std::array<uint8_t, 2> dataArray = {dataMSB, dataLSB};
    clockPin.write(1);
    {auto spi_trans = spi_bus.transaction(enablePin);
        spi_trans.write(dataArray);
    }
    hwlib::wait_ms(10);
}