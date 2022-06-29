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
//
//int main() {
//
//
//    // Tests:
//
//    // Set numkeys in numkeys.hpp to 2, and comment out the code above this to use
//    // Hook up the chip using pin 25 for the fsync pin, 26 for the SCLK pin and 24 for the SDATA pin along with two active-low buttons to pins 27 and 28
//    // It is easiest to test using an oscilloscope but an app might work as well, for checking wave shapes and frequencies
//    // To test phase you need to hook the output signal up to an oscilloscope, and use a function generator to generate a second wave with the same frequency and waveshape, then trigger on that wave.
//    // When you change the phase output on the chip, you'll see the wave move in comparison to the reference one
//
//    // Library tests
//    WDT->WDT_MR = WDT_MR_WDDIS;
//
//
//    auto testPinEnable = hwlib::target::pin_out(target::pins::d25);
//    auto testPinClock = hwlib::target::pin_out(target::pins::d26);
//    auto testPinData = hwlib::target::pin_out(target::pins::d24);
//
//
//    const int testMasterClock = 25000000;
//
//    auto testSpibus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(testPinClock, testPinData, hwlib::pin_in_dummy);
//
//    auto testChip = soundchip::ad9833(testPinEnable, testPinClock, testSpibus, testMasterClock);
//    testChip.setWave(SINE);
//    testChip.setFreq(1000);
//    testChip.enableOutput();
//    hwlib::wait_ms(1000); // Play a 1k sine wave for a second
//    testChip.setWave(TRIANGLE);
//    hwlib::wait_ms(1000); // Play a 1k triangle wave for a second
//    testChip.setWave(SQUARE);
//    hwlib::wait_ms(1000); // Play a 1k square wave for a second
//    testChip.setWave(HALF_SQUARE);
//    hwlib::wait_ms(1000); // Play a 1k half square wave for a second
//
//    testChip.setWave(SINE);
//
//    for (unsigned int i = 20; i < 20000; i++) {
//        testChip.setFreq(i); // Sweep through the entire hearable range
//    }
//
//    testChip.setFreq(1000);
//
//    for (unsigned int i = 0; i < 360; i++) {
//        testChip.setPhase(i); // Sweep through the entire phase range
//    }
//
//    testChip.disableOutput();
//
//
//    // Application tests
//
//
//    auto testKey1ActiveLow = hwlib::target::pin_in(target::pins::d27);
//    auto testKey2ActiveLow = hwlib::target::pin_in(target::pins::d28);
//    auto testKey1 = pin_in_invert(testKey1ActiveLow);
//    auto testKey2 = pin_in_invert(testKey2ActiveLow);
//
//    std::array < hwlib::pin_in * , NUMKEYS > testKeys = {&testKey1, &testKey2};
//
//    auto testKeyboard = keyboard::keyboardButtons(testKeys, noteC5);
//    auto testSynth = synthesizer::synthesizer(testChip, testKeyboard);
//
//    testSynth.playMajor(noteC4); // Play C major
//    testSynth.playMinor(noteC4); // Play C minor
//    testSynth.playChromatic(noteC4); // Play C chromatic
//
//    testSynth.soundEffect(); // Play a preprogrammed sound effect
//
//    for (unsigned int i = 0; i < 10; i++) {
//        testSynth.random(); // Play 10 random notes
//    }
//
//
//    long long startTime = hwlib::now_us();
//    long long currTime;
//
//    for (;;) { // You can play the keyboard for 10 seconds
//        currTime = hwlib::now_us();
//        if (currTime - startTime > 10000000) {
//            break;
//        }
//        testKeyboard.update();
//        testSynth.update();
//    }
//
//    testSynth.enableVibrato(20, 0.5);
//    startTime = hwlib::now_us();
//
//    for (;;) { // You can play the keyboard for 10 seconds, now with a dramatic vibrato effect
//        currTime = hwlib::now_us();
//        if (currTime - startTime > 10000000) {
//            break;
//        }
//        testKeyboard.update();
//        testSynth.update();
//    }
//
//    testSynth.disableVibrato();
//    synth.enableGlissando(0.3);
//    startTime = hwlib::now_us();
//
//    for (;;) { // You can play the keyboard for 10 seconds, now with a glissando effect
//        currTime = hwlib::now_us();
//        if (currTime - startTime > 10000000) {
//            break;
//        }
//        testKeyboard.update();
//        testSynth.update();
//    }
//
//    testSynth.disableGlissando();
//    synth.enablePhaseVibrato(200, 20);
//    startTime = hwlib::now_us();
//
//    for (;;) { // You can play the keyboard for 10 seconds, now with a phase vibrato effect
//        currTime = hwlib::now_us();
//        if (currTime - startTime > 10000000) {
//            break;
//        }
//        testKeyboard.update();
//        testSynth.update();
//    }
//
//    testSynth.disablePhaseVibrato();
//
//    // If you have more than one AD9833 chip, you can test polyphony here
//    // Hook up the second chip's fsync to pin 52, hook up the same SDATA and SCLK pins as the first chip
//    auto testEnablePin2 = hwlib::target::pin_out(target::pins::d52);
//    auto testChip2 = soundchip::ad9833(testEnablePin2, testPinClock, testSpibus, masterClock);
//    auto testSynth2 = synthesizer::synthesizer(testChip2, testKeyboard);
//
//    for (;;) { // You can play the keyboard for 10 seconds, now with two note polyphony
//        currTime = hwlib::now_us();
//        if (currTime - startTime > 10000000) {
//            break;
//        }
//        testKeyboard.update();
//        testSynth.update();
//        testSynth2.update();
//    }
//}