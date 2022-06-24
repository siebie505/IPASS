/// @file
///
/// \brief
///
/// \details
///
#include "soundchip.hpp"
#include "hwlib.hpp"


#ifndef ADCHIP_HPP
#define ADCHIP_HPP

namespace soundchip {
class ad9833 : public soundchip {
    private:
        hwlib::pin_out& enablePin;
        hwlib::pin_out& clockPin;
        int masterClock;
        float freqReg0, freqReg1;
        int phaseReg0, phaseReg1;
        bool dacOff, intClockOff, resetOn, chooseFreqReg1, choosePhaseReg1;
        waveType wavetype;

        const uint16_t modeBit = 0b0000000000000010;
        const uint16_t div2Bit = 0b0000000000001000;
        const uint16_t opbitenBit = 0b0000000000100000;
        const uint16_t sleep12Bit = 0b0000000001000000; // dac uit
        const uint16_t sleep1Bit = 0b0000000010000000; // internal clock uit
        const uint16_t resetBit = 0b0000000100000000;
        const uint16_t phaseSelectBit = 0b0000010000000000;
        const uint16_t freqSelectBit = 0b0000100000000000;
        const uint16_t hlbBit = 0b0001000000000000; // als je niet 2 freq register writes achter elkaar doet kies je hiermee of je de 14 lsb of 14 msb wil schrijven (deze bit op 0 is 14 lsb)
        const uint16_t b28Bit = 0b0010000000000000; // 2 freq register writes achter elkaar doen
        const uint16_t freqReg0Bit = 0b0100000000000000;
        const uint16_t freqReg1Bit = 0b1000000000000000;
        const uint16_t phaseReg0Bit = 0b1100000000000000;
        const uint16_t phaseReg1Bit = 0b1110000000000000;

        const float twoPi = 6.28319;
        const long long twoPow32 = 4294967296;
        const unsigned int twoPow12 = 4096;
        const unsigned int lsbMaskFreq = 16383; // 0b11111111111111
        const unsigned int msbMaskFreq = 268419072; // 0b1111111111111100000000000000
        const unsigned int maskPhase = 4095; // 0b111111111111
        const unsigned int lsbMaskControl = 255; // 0b11111111
        const unsigned int msbMaskControl = 65280; // 0b1111111100000000
        const unsigned int totalDegrees = 360;

        hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus;


        void writeControl();

        void reset();

        void writeTwoBytes(const uint16_t& data);

        void writeFreq(const int& registerNum);

        void writePhase(const int& registerNum);



    public:
        ad9833(hwlib::pin_out& enablePin_p, hwlib::pin_out& clockPin_p, hwlib::spi_bus_bit_banged_sclk_mosi_miso& spi_bus, const int& masterClock); // maak pins aan met de goede types, zet de enable pin hoog

        void setFreq(const float& freq, const int& registerNum = 0);

        void setPhase(const int& phase, const int& registerNum = 0);

        void setFreq(const float& freqHz) override;

        void setPhase(const int& phaseDeg) override;

        void setWave (const waveType& wavetype_p) override;

        void enableOutput (const int& freqReg = 0, const int& phaseReg = 0);

        void enableOutput() override;



        void disableOutput () override;

    };

}

#endif /* ADCHIP_HPP */
