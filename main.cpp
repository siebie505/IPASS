#include "hwlib.hpp"
#include "ADCHIP.hpp"
#include "synthesizer.hpp"
#include "soundchip.hpp"
#include "keyboard.hpp"
#include "pin_in_invert.hpp"
#include "keyboardButtons.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto pinEnable = hwlib::target::pin_out(3, 0); // pin 25, oranje
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

    const int num_keys = 13;

    std::array<hwlib::pin_in*, num_keys> keys = {&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key10, &key11, &key12, &key13};

    auto keyboard = keyboard::keyboardButtons(keys);
    auto synth = synthesizer::synthesizer(ad9833, keyboard);

    synth.setWave(SINE);
//    synth.enableGlissando();

    std::array<synthesizer::synthesizer*, 1 > synths = {&synth};

    std::array<keyboard::keyboard*, 1 > keyboards = {&keyboard};

    for(;;) {
        for(keyboard::keyboard* keyboardCurrent : keyboards) {
            keyboardCurrent->update();
        }
        for(synthesizer::synthesizer* synthCurrent : synths) {
            synthCurrent->update();
        }
    }
}