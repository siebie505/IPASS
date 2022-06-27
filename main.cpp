#include "hwlib.hpp"
#include "ADCHIP.hpp"
#include "synthesizer.hpp"
#include "soundchip.hpp"
#include "keyboard.hpp"
#include "pin_in_invert.hpp"
#include "keyboardButtons.hpp"
#include "numkeys.hpp"
#include "notes.hpp"



int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto pinEnable = hwlib::target::pin_out(3, 0); // pin 25, wit
    auto pinClock = hwlib::target::pin_out(3, 1); // pin 26, groen
    auto pinData = hwlib::target::pin_out(0, 15); // pin 24, blauw
    const int masterClock = 25000000;

    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(pinClock, pinData, hwlib::pin_in_dummy);

    auto ad9833 = soundchip::ad9833(pinEnable, pinClock, spi_bus, masterClock);




    auto key1ActiveLow = hwlib::target::pin_in(3, 2);
    auto key2ActiveLow = hwlib::target::pin_in(3, 3);
    auto key3ActiveLow = hwlib::target::pin_in(3, 6);
    auto key4ActiveLow = hwlib::target::pin_in(3, 9);
    auto key5ActiveLow = hwlib::target::pin_in(0, 7);
    auto key6ActiveLow = hwlib::target::pin_in(3, 10);
    auto key7ActiveLow = hwlib::target::pin_in(2, 1);
    auto key8ActiveLow = hwlib::target::pin_in(2, 2);
    auto key9ActiveLow = hwlib::target::pin_in(2, 3);
    auto key10ActiveLow = hwlib::target::pin_in(2, 4);
    auto key11ActiveLow = hwlib::target::pin_in(2, 5);
    auto key12ActiveLow = hwlib::target::pin_in(2, 6);
    auto key13ActiveLow = hwlib::target::pin_in(2, 7);


    auto key1 = pin_in_invert(key1ActiveLow);
    auto key2 = pin_in_invert(key2ActiveLow);
    auto key3 = pin_in_invert(key3ActiveLow);
    auto key4 = pin_in_invert(key4ActiveLow);
    auto key5 = pin_in_invert(key5ActiveLow);
    auto key6 = pin_in_invert(key6ActiveLow);
    auto key7 = pin_in_invert(key7ActiveLow);
    auto key8 = pin_in_invert(key8ActiveLow);
    auto key9 = pin_in_invert(key9ActiveLow);
    auto key10 = pin_in_invert(key10ActiveLow);
    auto key11 = pin_in_invert(key11ActiveLow);
    auto key12 = pin_in_invert(key12ActiveLow);
    auto key13 = pin_in_invert(key13ActiveLow);

    std::array<hwlib::pin_in*, NUMKEYS> keys = {&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key10, &key11, &key12, &key13};
//    std::array<hwlib::pin_in*, NUMKEYS> keys = {&key1};

    auto keyboard = keyboard::keyboardButtons(keys, noteC5); // startNoot mag vanaf C0 tot en met het aantal toetsen dat je hebt terug vanaf B8, dus als je 13 toetsen hebt ga je 13 noten terug vanaf B8 (dus B7)
    auto synth = synthesizer::synthesizer(ad9833, keyboard);

    synth.setWave(SINE);
//    synth.enableVibrato(50, 5);
    synth.enablePhaseVibrato(5, 2);
//    synth.enableGlissando(1);

    std::array<synthesizer::synthesizer*, 1 > synths = {&synth};

    for(;;) {
        for(synthesizer::synthesizer* synthCurrent : synths) {
            synthCurrent->update();
        }
    }
}