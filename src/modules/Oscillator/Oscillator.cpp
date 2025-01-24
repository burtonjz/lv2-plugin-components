#include "modules/Oscillator/Oscillator.hpp"
#include "modules/ModuleType.hpp"
#include "modules/Oscillator/Waveform.hpp"
#include "modules/Oscillator/Wavetable.hpp"


#include <array>
#include <cstdint>
#include <cmath>



#ifdef DEBUG
#include <iostream>
#endif


Module::Oscillator::Oscillator(PluginResources res, double sampleRate):
    Module::Module(res, sampleRate, ModuleType::Oscillator,0,1),
    phase_(0),
    increment_(0)
{
    Wavetable::generate();

    
    // set parameters
    LV2_ATOM_TYPE(ParameterType::BYPASS)* atom = res_.state->getAtom<ParameterType::BYPASS>(type_);
    Parameter p = Parameter(
        ParameterType::BYPASS,
        res_.uridMap, 
        res_.uridMap->map(res_.uridMap->handle, res.urids->getPlugURID(type_, ParameterType::BYPASS)
    );
    // We need a reverse lookup between URID -> URI, and we need to figure out how to send the atom over.
    // this should probably be simplified and encapsulated within the Parameter logic if possible, or somewhere else so
    // we don't blow up the module initializations with hot garbage
}



//     outputBuffer_(),
//     phase_(0),
//     increment_(0)
// {    
//     parameterController_.addParameter<ParameterType::STATUS>(true,false);
//     parameterController_.addParameter<ParameterType::WAVEFORM>(parameterDefaults[static_cast<int>(ParameterType::WAVEFORM)],false);
//     parameterController_.addParameter<ParameterType::AMPLITUDE>(1.0, true);
//     parameterController_.addParameter<ParameterType::GAIN>(1.0, true);
//     parameterController_.addParameter<ParameterType::PHASE>(0.0, true);
//     parameterController_.addParameter<ParameterType::PAN>(0.0, true);
//     parameterController_.addParameter<ParameterType::DETUNE>(0.0, true);

//     if(sampleRate_) parameterController_.addParameter<ParameterType::FREQUENCY>(440.0,true,0.0, *sampleRate_/2.0);
//     else parameterController_.addParameter<ParameterType::FREQUENCY>(440.0,true);
// }

// bool Oscillator::isOutputBufferSet(){
//     for (size_t i = 0; i < AudioPorts::AUDIO_N; ++i ){
//         if(outputBuffer_.get(i) == nullptr) return false ;
//     }
//     return true ;
// }

// void Oscillator::processSample(uint32_t idx){
//     // only process sample if output buffer exists and module has status
//     if(!parameterController_.getParameterValue<ParameterType::STATUS>()) return ;
//     if(!isOutputBufferSet()) return ;

//     panSample(getSample(),idx);
// }

// double Oscillator::getSample() const {
//     const std::array<double,CONFIG_OSCILLATOR_WAVETABLE_SIZE>* wave_ptr;
//     double p, index, frac, sample ;
//     int index_floor ;

//     wave_ptr = Wavetable::getWavetable(static_cast<Waveform>(parameterController_.getParameterValue<ParameterType::WAVEFORM>()));

//     // linear interpolation of wavetable lookup value
//     p = std::fmod(phase_ + parameterController_.getParameterInstantaneousValue<ParameterType::PHASE>(),1.0);
    
//     index = p * (CONFIG_OSCILLATOR_WAVETABLE_SIZE - 1);
//     index_floor = static_cast<int>(std::floor(index));
//     frac = index - index_floor ;

//     sample = (1.0 - frac) * (*wave_ptr)[index_floor] + frac * (*wave_ptr)[index_floor + 1];

//     sample *= parameterController_.getParameterInstantaneousValue<ParameterType::AMPLITUDE>();
//     sample *= parameterController_.getParameterInstantaneousValue<ParameterType::GAIN>();

//     return sample ;
// }

// void Oscillator::tick(){
//     if (!sampleRate_) return ;

//     increment_ = parameterController_.getParameterInstantaneousValue<ParameterType::FREQUENCY>() / *sampleRate_ ;
//     phase_ = std::fmod(phase_ + increment_, 1.0);

//     parameterController_.modulate();
// }

// void Oscillator::panSample(double sample_value, uint32_t idx){
//     if (AudioPorts::AUDIO_N == 1) outputBuffer_.addToBuffer(sample_value, idx, AudioPorts::AUDIO_L );

//     if (AudioPorts::AUDIO_N == 2 ){
//         double v = parameterController_.getParameterInstantaneousValue<ParameterType::PAN>() / 2.0 + 0.5 ;
//         outputBuffer_.addToBuffer(v * sample_value, idx, AudioPorts::AUDIO_L );
//         outputBuffer_.addToBuffer((1.0 - v) * sample_value, idx, AudioPorts::AUDIO_R );
//     }
    
//     else {
//         throw std::invalid_argument("Only 1 or 2 Audio Outputs are currently supported.");
//     }

// }
