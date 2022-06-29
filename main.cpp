//#include "hwlib.hpp"
//#include "ADCHIP.hpp"
//#include "synthesizer.hpp"
//#include "soundchip.hpp"
//#include "keyboard.hpp"
//#include "pin_in_invert.hpp"
//#include "keyboardButtons.hpp"
//#include "numkeys.hpp"
//#include "notes.hpp"
//
//
//
//int main() {
//    // Disable the watchdog
//    WDT->WDT_MR = WDT_MR_WDDIS;
//
//
//    auto pinEnable = hwlib::target::pin_out(hwlib::target::pins::d25);
//    auto pinClock = hwlib::target::pin_out(hwlib::target::pins::d26);
//    auto pinData = hwlib::target::pin_out(hwlib::target::pins::d24);
//    auto pinEnable2 = hwlib::target::pin_out(hwlib::target::pins::d52);
//    const int masterClock = 25000000;
//
//    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(pinClock, pinData, hwlib::pin_in_dummy);
//
//    auto ad9833 = soundchip::ad9833(pinEnable, pinClock, spi_bus, masterClock);
//
//
//    auto chip2 = soundchip::ad9833(pinEnable2, pinClock, spi_bus, masterClock);
//
//    auto key1ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d27);
//    auto key2ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d28);
//    auto key3ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d29);
//    auto key4ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d30);
//    auto key5ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d31);
//    auto key6ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d32);
//    auto key7ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d33);
//    auto key8ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d34);
//    auto key9ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d35);
//    auto key10ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d36);
//    auto key11ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d37);
//    auto key12ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d38);
//    auto key13ActiveLow = hwlib::target::pin_in(hwlib::target::pins::d39);
//
//
//    auto key1 = pin_in_invert(key1ActiveLow);
//    auto key2 = pin_in_invert(key2ActiveLow);
//    auto key3 = pin_in_invert(key3ActiveLow);
//    auto key4 = pin_in_invert(key4ActiveLow);
//    auto key5 = pin_in_invert(key5ActiveLow);
//    auto key6 = pin_in_invert(key6ActiveLow);
//    auto key7 = pin_in_invert(key7ActiveLow);
//    auto key8 = pin_in_invert(key8ActiveLow);
//    auto key9 = pin_in_invert(key9ActiveLow);
//    auto key10 = pin_in_invert(key10ActiveLow);
//    auto key11 = pin_in_invert(key11ActiveLow);
//    auto key12 = pin_in_invert(key12ActiveLow);
//    auto key13 = pin_in_invert(key13ActiveLow);
//
//    std::array<hwlib::pin_in*, NUMKEYS> keys = {&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key10, &key11, &key12, &key13};
//
//    auto keyboard = keyboard::keyboardButtons(keys, noteC5); // startNote can be beween C0 up to and including  (the amount of keys you have) back from B8, so if you have 13 keys the max is B7 (13 back from B8)
//    auto synth = synthesizer::synthesizer(ad9833, keyboard);
//    auto synth2 = synthesizer::synthesizer(chip2, keyboard);
//
//    synth.setWave(SQUARE);
////    synth.enableVibrato(20, 0.5);
////    synth.enablePhaseVibrato(200, 20);
////    synth.enableGlissando(0.3);
//    synth2.setWave(SQUARE);
//
//    std::array<synthesizer::synthesizer*, 2 > synths = {&synth, &synth2};
//
//    for(;;) {
//        keyboard.update();
//        for(synthesizer::synthesizer* synthCurrent : synths) {
//            synthCurrent->update();
//        }
//    }
//}