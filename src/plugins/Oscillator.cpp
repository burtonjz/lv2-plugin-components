#include "plugins/Oscillator.hpp"

// Constructor
Plugin::Oscillator::Oscillator(const double sampleRate, const LV2_Feature *const *features):
    LV2Plugin(sampleRate, features),
    connectionManager_(),
    keyboardController_(sampleRate),
    oscillator_(sampleRate)
{}

void Plugin::Oscillator::connectPort(const uint32_t port, void* data){

}

void Plugin::Oscillator::activate(){

}

void Plugin::Oscillator::run(const uint32_t sampleCount){

}

void Plugin::Oscillator::deactivate(){

}
