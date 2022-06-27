#include "glissando.hpp"

using namespace effects;

glissando::glissando(effects::vibrato &vibrato1) : vibrato1(vibrato1) {}

void glissando::update() {

}

void glissando::setAll(const float& currentNote_p, const float& lastNote_p, const bool &glissandoOn_p, int glissandoTime_p, int glissandoCooldown_p) {
    glissandoOn = glissandoOn_p;
    glissandoCooldown = glissandoCooldown_p;
    glissandoTime = glissandoTime_p;
}