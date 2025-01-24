#include "midi/KeyboardObserver.hpp"

void KeyboardObserver::onKeyPressed(const Note* note){
}

void KeyboardObserver::onKeyReleased(Note note){
}

void KeyboardObserver::onPitchbend(uint16_t pitchbend ){
}

void KeyboardObserver::onMidiControlEvent(LV2_Midi_Controller messageType, uint8_t value){
}
