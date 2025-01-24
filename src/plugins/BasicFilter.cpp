#include "plugins/BasicFilter.hpp"
#include "plugins/LV2Plugin.hpp"


BasicFilter::BasicFilter(const double sampleRate, const LV2_Feature *const *features):
    LV2Plugin(sampleRate,features)
{}

// API FUNCTIONS
void BasicFilter::connectPort(const uint32_t port, void* data){

}

void BasicFilter::activate(){

}

void BasicFilter::run(const uint32_t sampleCount){

}

void BasicFilter::deactivate(){

}
