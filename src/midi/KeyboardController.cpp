#include "midi/KeyboardController.hpp"
#include "plugin.hpp"
#include PLUG_CONFIG
#include <cmath>

KeyboardController::KeyboardController(double sampleRate):
    sampleRate_(sampleRate),
    pitchbend_(8192),
    sustain_(0)
{}

void KeyboardController::initialize(){
    computePitchbendScaleFactor();
    Note::initialize(); // precompute note frequencies using sample rate
}

void KeyboardController::registerObserver(KeyboardObserver* observer){
    observers_.push_back(observer);
}

void KeyboardController::processMidi(LV2_Midi_Message_Type message_type, const uint8_t* const msg){
    switch(message_type){
    case LV2_MIDI_MSG_NOTE_ON:
        notes_[msg[1]].setMidiNote(msg[1]);
        notes_[msg[1]].setMidiVelocity(msg[2]);
        notes_[msg[1]].setIsOn(true);
        notifyMidiNoteOn(&notes_[msg[1]]);
        break ;
    case LV2_MIDI_MSG_NOTE_OFF:
        notes_[msg[1]].setIsOn(false);
        notifyMidiNoteOff(notes_[msg[1]]);
        notes_.erase(msg[1]);
        break ;
    case LV2_MIDI_MSG_BENDER:
        setPitchbend(static_cast<uint16_t>((msg[2] << 7) | msg[1]));
        notifyMidiPitchbend();
        break ;
    case LV2_MIDI_MSG_CONTROLLER:
        if ( msg[1] == LV2_MIDI_CTL_SUSTAIN ) setSustain(msg[2]);
        notifyMidiControlEvent(static_cast<LV2_Midi_Controller>(msg[1]), msg[2]);
        break ;
    default:
        break ;
    }
}

void KeyboardController::notifyMidiNoteOn(const Note* note) const {
    for ( auto observer : observers_ ){
        observer->onKeyPressed(note);
    }
}

void KeyboardController::notifyMidiNoteOff(Note note) const {
    for ( auto observer: observers_ ){
        observer->onKeyReleased(note);
    }
}

void KeyboardController::notifyMidiPitchbend() const {
    for ( auto observer : observers_ ){
        observer->onPitchbend(pitchbend_);
    }
}

void KeyboardController::notifyMidiControlEvent(LV2_Midi_Controller ctrl, uint8_t value) const {
    for ( auto observer : observers_ ){
        observer->onMidiControlEvent(ctrl, value);
    }
}

float KeyboardController::getPitchbend() const {
    return pitchbend_ ;
}

uint8_t KeyboardController::getSustain() const {
    return sustain_ ;
}

void KeyboardController::setSustain(uint8_t sustain){
    if ( sustain > 127 ) sustain_ = 127 ;
    else sustain_ = sustain ;
}


void KeyboardController::computePitchbendScaleFactor(){
    float shiftValue ;
    for ( uint16_t i = 0; i < 16384; ++i ){
        shiftValue = ( i - 8192.0 ) / 16383.0 * CONFIG_PITCHBEND_MAX_SHIFT * 2.0 ; 
        pitchbendScaleFactor_[i] = std::pow(2.0f, (shiftValue / 12.0f));
    }
}

void KeyboardController::tick(double time){
    for ( auto it = notes_.begin(); it != notes_.end(); ){
        it->second.tick(time);
    }
}
