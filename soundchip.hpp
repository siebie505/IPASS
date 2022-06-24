#ifndef SOUNDCHIP_HPP
#define SOUNDCHIP_HPP

enum waveType{SINE, TRIANGLE, SQUARE, HALF_SQUARE};

namespace soundchip {
    class soundchip {
    public:
        soundchip() {}
        virtual void setFreq(const float& freq_hz) = 0;
        virtual void setPhase(const int& phase_deg) = 0;
        virtual void setWave(const waveType& wavetype) = 0;
        virtual void enableOutput() = 0;
        virtual void disableOutput() = 0;
    };
}

#endif /* SOUNDCHIP_HPP */
