// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file

#include "soundchip.hpp"
#include "hwlib.hpp"


#ifndef ADCHIP_HPP
#define ADCHIP_HPP

namespace soundchip {

/// A AD9833 soundchip
///
/// This class abstracts the control of a AD9833 chip

class ad9833 : public soundchip {
    private:
        /// The enablepin for the chip (needs to be unique to each chip)
        hwlib::pin_out& enablePin;

        /// The Clockpin for the chip (can be shared between multiple AD9833 chips)
        hwlib::pin_out& clockPin;

        /// The frequency of the master clock controlling the AD9833 chip, 25MHz for the module. (Not the same as the SPI clock)
        int masterClock;

        /// Frequencies stored in the two frequency registers
        float freqReg0, freqReg1;

        /// Phase values stored in the two phase registers
        int phaseReg0, phaseReg1;

        /// Values for wether the AD9833's DAC, and internal clock are turned off (to save power), wether the chip is in reset mode
        /// (for turning off the output) and which frequency and phase registers are used for output
        bool dacOff, intClockOff, resetOn, chooseFreqReg1, choosePhaseReg1;

        /// The used type of waveform is stored here (SINE, TRIANGLE, SQUARE OR HALF_SQUARE)
        waveType wavetype;

        /// One of the bits sent in the control bytes to set the waveform
        const uint16_t modeBit = 0b0000000000000010;

        /// One of the bits sent in the control bytes to set the waveform
        const uint16_t div2Bit = 0b0000000000001000;

        /// One of the bits sent in the control bytes to set the waveform
        const uint16_t opbitenBit = 0b0000000000100000;

        /// The bit sent in the control bytes to turn off the DAC
        const uint16_t sleep12Bit = 0b0000000001000000;

         /// The bit sent in the control bytes to turn off the internal clock
        const uint16_t sleep1Bit = 0b0000000010000000;

        /// The bit sent in the control bytes to reset the chip (disabled the output, doesn't reset frequency and phase registers)
        const uint16_t resetBit = 0b0000000100000000;

        /// The bit sent in the control bytes to choose which phase register to output
        const uint16_t phaseSelectBit = 0b0000010000000000;

        /// The bit sent in the control bytes to choose which frequency register to output
        const uint16_t freqSelectBit = 0b0000100000000000;

        /// The bit sent in the control bytes to choose wether to send the 14 LSB or 14 MSB to the frequency register (when not turned on the 14 LSB will be expected) it doesn't matter what this is set to if the B28 bit is set
        const uint16_t hlbBit = 0b0001000000000000;

        /// The bit sent in the control bytes to choose wether to send the 14 LSB and 14 MBS to the frequency register directly after one another
        const uint16_t b28Bit = 0b0010000000000000;

        /// The bit sent to choose to write to frequency register 0
        const uint16_t freqReg0Bit = 0b0100000000000000;

        /// The bit sent to choose to write to frequency register 1
        const uint16_t freqReg1Bit = 0b1000000000000000;

        /// The bits sent to choose to write to phase register 0
        const uint16_t phaseReg0Bit = 0b1100000000000000;

        /// The bits sent to choose to write to phase register 1
        const uint16_t phaseReg1Bit = 0b1110000000000000;

        /// An approximation of two times Pi used to write to the phase registers
        const float twoPi = 6.28319;

        /// The value of 2^28 used to to write to the frequency registers
        const long long twoPow28 = 268435456;

        /// The value of 2^12 used to write to the phase registers
        const uint16_t twoPow12 = 4096;

        /// A mask to easily select the 14 LSB of the frequency value
        const int lsbMaskFreq = 0b11111111111111;

        /// A mask to easily select the 14 MSB of the frequency value
        const int msbMaskFreq = 0b1111111111111100000000000000;

        /// A mask to easily select 12 bits of the phase value to write to the register
        const int maskPhase = 0b111111111111;

        /// A mask to easily select the 8 LSB of control bytes
        const int lsbMaskControl = 0b11111111;

        /// A mask to easily select the 8 MSB of control bytes
        const int msbMaskControl = 0b1111111100000000;

        /// Max value for the phase
        const int totalDegrees = 360;

        /// An spi bus to communicate with the chip
        hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus;

        /// A function to write all the set information to the chip with 2 control bytes
        void writeControl();

        /// A sequence of values to set to defaults
        void reset();

        /// A simple function that will write two bytes to the chip
        void writeTwoBytes(const uint16_t& data);

        /// A function that will write the set frequency value to the selected register
        void writeFreq(const int& registerNum);

        /// A function that will write the set phase value to the selected register
        void writePhase(const int& registerNum);



    public:
        /// Create an AD9833 object by giving the enablepin spefific to the chip, an spi bus and it's clock pin separately and the frequency of the masterclock
        ad9833(hwlib::pin_out& enablePin_p, hwlib::pin_out& clockPin_p, hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus, const int& masterClock);

        /// A function that will write the given frequency to the given register
        void setFreq(const float& freq, const int& registerNum);

        /// A function that will write the given phase to the given register
        void setPhase(const int& phase, const int& registerNum);

        /// A function that will write the given frequency to register 0
        void setFreq(const float& freqHz) override;

        /// A function that will write the given phase to register 0
        void setPhase(const int& phaseDeg) override;

        /// A function that will change the shape of the wave, possible choices are SINE, TRIANGLE, SQUARE or HALF_SQUARE
        void setWave (const waveType& wavetype_p) override;

        /// A function that will enable the output of the chip, using the given registers
        void enableOutput (const int& freqReg, const int& phaseReg);

        /// A function that will enable the output of the chip, using frequency and phase register 0
        void enableOutput() override;


        /// A function that will disable the output of the chip
        void disableOutput () override;

    };

}

#endif /* ADCHIP_HPP */
