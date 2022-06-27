#include "vibrato.hpp"
#include "phaseVibrato.hpp"
#include "soundchip.hpp"

#ifndef GLISSANDO_HPP
#define GLISSANDO_HPP

namespace effects {
    class glissando {
    private:
        effects::vibrato& vibrato1;
        bool glissandoOn = false;
        bool glissandoDone = false;
        int glissandoTime = 5;
//        int glissandoCooldown = 5;
        float currentNote = 1000;
        float lastNote = 1000;
        float currentFreq = 0;

        int iteration = 0;
        long long timeSinceLastUpdate = 0;
    public:
        glissando(effects::vibrato& vibrato1);

        void set(const bool& glissandoOn_p, const int& glissandoTime_p);
        void setNotes(const float& currentNote_p, const float& lastNote_p);
        bool getGlissandoDone();
//        , int glissandoCooldown_p

        void update();
    };
}

#endif //* GLISSANDO_HPP */
