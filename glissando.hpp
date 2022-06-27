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
        int glissandoTime = 5;
        int glissandoCooldown = 5;
        float currentNote = 1000;
        float lastNote = 1000;
    public:
        glissando(effects::vibrato& vibrato1);

        void setAll(const float& currentNote_p, const float& lastNote_p, const bool& glissandoOn_p, int glissandoTime_p, int glissandoCooldown_p);

        void update();
    };
}

#endif //* GLISSANDO_HPP */