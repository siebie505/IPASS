//#include "synthesizer.hpp"
//#include "note.hpp"
//
//note::note::note(synthesizer& synth, const float& freq, const int& phase, const bool& vibrato, const bool& phaseVibrato, const int& vibratoSpeed, const int& vibratoDepth, const int& phaseVibratoSpeed, const int& phaseVibratoDepth) : synth(synth), startFreq(freq), startPhase(phase), vibrato(vibrato), phaseVibrato(phaseVibrato), vibratoSpeed(vibratoSpeed), vibratoDepth(vibratoDepth), phaseVibratoSpeed(phaseVibratoSpeed), phaseVibratoDepth(phaseVibratoDepth) {
//    synth.setFreq(freq);
//    synth.setPhase(phase);
//    synth.play();
//}
//
//void note::note::stop() {
//    synth.stop();
//}
//
//
//void note::note::changeNote(const float& freq_p, const int& phase_p, const bool& vibrato_p, const bool& phaseVibrato_p,
//                            const int& vibratoSpeed_p, const int& vibratoDepth_p, const int& phaseVibratoSpeed_p,
//                            const int& phaseVibratoDepth_p) {
//    startFreq = freq_p;
//    startPhase = phase_p;
//    vibrato = vibrato_p;
//    phaseVibrato = phaseVibrato_p;
//    vibratoSpeed = vibratoSpeed_p;
//    vibratoDepth = vibratoDepth_p;
//    phaseVibratoSpeed = phaseVibratoSpeed_p;
//    phaseVibratoDepth = phaseVibratoDepth_p;
//
//}
//
//
//void note::note::update() {
////    long long currTime = hwlib::now_us();
////    switch(state) {
////        case state1:
////            if(currTime - state1StartTime > threshold) {
////                state = state2;
////                state2StartTime = hwlib::now_us();
////                state2.do();
////            }
////            break;
////        case state2:
////            break;
////    }
//    if(vibrato) {
//        vibratoUpdate();
//    }
//    if(phaseVibrato) {
//        phaseVibratoUpdate();
//    }
//}
