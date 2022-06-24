#include "hwlib.hpp"
#include "ADCHIP.hpp"
#include "synthesizer.hpp"
#include "soundchip.hpp"
#include "keyboard.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto pinEnable = hwlib::target::pin_out(3, 0); // pin 25, oranje
    auto pinClock = hwlib::target::pin_out(3, 1); // pin 26, groen
    auto pinData = hwlib::target::pin_out(0, 15); // pin 24, blauw
    const int masterClock = 25000000;

    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(pinClock, pinData, hwlib::pin_in_dummy);

    auto ad9833 = soundchip::ad9833(pinEnable, pinClock, spi_bus, masterClock);


    auto key1 = hwlib::target::pin_in(3, 2);
    auto key2 = hwlib::target::pin_in(3, 3);
    auto key3 = hwlib::target::pin_in(3, 6);
    auto key4 = hwlib::target::pin_in(3, 9);
    auto key5 = hwlib::target::pin_in(0, 7);
    auto key6 = hwlib::target::pin_in(3, 10);
    auto key7 = hwlib::target::pin_in(2, 1);
    auto key8 = hwlib::target::pin_in(2, 2);
    auto key9 = hwlib::target::pin_in(2, 3);
    auto key10 = hwlib::target::pin_in(2, 4);
    auto key11 = hwlib::target::pin_in(2, 5);
    auto key12 = hwlib::target::pin_in(2, 6);
    auto key13 = hwlib::target::pin_in(2, 7);

    const int num_keys = 13;

    std::array<hwlib::pin_in*, num_keys> keys = {&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key10, &key11, &key12, &key13};

    auto keyboard = keyboard::keyboard(keys);
    auto synth = synthesizer::synthesizer(ad9833, keyboard);

    synth.setWave(SINE);
//    synth.enableGlissando();
    synth.setFreq(1000);
    synth.play();
    while(true) {
        // 360 een const maken
        // 10 een parameter, speed
        for (unsigned int i = 0; i < 360; i+=10) {
            synth.setPhase(i);
            hwlib::cout << i << "\n";
        }
        for (unsigned int i = 360; i > 0; i-=10) {
            synth.setPhase(i);
            hwlib::cout << i << "\n";
        }

    }

//    std::array<synthesizer::synthesizer*, 1 > synths = {&synth};
//    for(;;) {
//        for(synthesizer::synthesizer* synthCurrent : synths) {
//            synthCurrent->update();
//        }
//    }
}