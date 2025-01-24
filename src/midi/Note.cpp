#include "midi/Note.hpp"
#include <cmath>

void Note::initialize(){
    for ( uint8_t i = 0 ; i < 128 ; ++i ){
        frequencies_[i] = std::pow(2.0, (static_cast<double>(i) - 69.0) / 12.0) * 440.0 ;
    }
}

Note::Note(uint8_t midiNote, uint8_t midiVelocity, bool midiOn):
    midiNote_(midiNote),
    midiVelocity_(midiVelocity),
    midiOn_(midiOn),
    time_(0)
{}

uint8_t Note::getMidiNote() const {
    return midiNote_ ;
}

void Note::setMidiNote(uint8_t note ){
    if ( note > 127 ) midiNote_ = 127 ;
    else midiNote_ = note ;
}

uint8_t Note::getMidiVelocity() const {
    return midiVelocity_ ;
}

void Note::setMidiVelocity(uint8_t velocity){
        if ( velocity > 127 ) midiVelocity_ = 127 ;
        else midiVelocity_ = velocity ;
}

bool Note::getMidiOn() const {
    return midiOn_ ;
}

void Note::setIsOn(bool midiOn){
    if ( midiOn_ != midiOn ){
        midiOn_ = midiOn ;
        time_ = 0 ;
    }
}

double Note::getFrequency(uint8_t note){
    if ( note > 127 ) return frequencies_[127] ;
    return frequencies_[note] ;
}

double Note::getFrequency() const {
    return frequencies_[midiNote_] ;
}

float Note::getTime() const {
    return time_ ;
}

void Note::tick(double time){
    time_ += time ;
}
