#ifndef __OSCILLATOR_CONFIG_HPP_
#define __OSCILLATOR_CONFIG_HPP_


#include <cstddef>
#include <unordered_map>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>

#include "plugin.hpp"
#include "modules/ModuleType.hpp"
#include "params/Parameter.hpp"
#include "params/ParameterType.hpp"



// These configuration items are required for any config:

// DEFINE URIDS AND INITIALIZE MAP
struct Urids {
    LV2_URID plugin ;
    LV2_URID midiEvent ;
    // ATOM
    LV2_URID atomPath ;
    LV2_URID atomResource ;
    LV2_URID atomSequence ;
    LV2_URID atomURID ;
    LV2_URID atomEventTransfer ;
    // PATCH
    LV2_URID patchGet ;
    LV2_URID patchSet ;
    LV2_URID patchPut ;
    LV2_URID patchBody ;
    LV2_URID patchSubject ;
    LV2_URID patchProperty ;
    LV2_URID patchValue ;
    // PLUGIN
    LV2_URID plugBypass ;
    LV2_URID plugWaveform ;
    LV2_URID plugFrequency ;
    LV2_URID plugAmplitude ;
    LV2_URID plugGain ;
    LV2_URID plugPhase ;

    // for looking up plugin URIs
    std::unordered_map<ModuleType, std::unordered_map<ParameterType,LV2_URID>> plugMap ;

    void initialize(LV2_URID_Map* m){
        // standard URIs (DO NOT TOUCH)
        plugin            = m->map(m->handle, PLUG_URI);
        midiEvent         = m->map(m->handle, LV2_MIDI__MidiEvent);
        atomPath          = m->map(m->handle, LV2_ATOM__Path);
        atomResource      = m->map(m->handle, LV2_ATOM__Resource);
        atomSequence      = m->map(m->handle, LV2_ATOM__Sequence);
        atomURID          = m->map(m->handle, LV2_ATOM__URID);
        atomEventTransfer = m->map(m->handle, LV2_ATOM__eventTransfer);
        patchGet          = m->map(m->handle, LV2_PATCH__Get);
        patchSet          = m->map(m->handle, LV2_PATCH__Set);
        patchPut          = m->map(m->handle, LV2_PATCH__Put);
        patchBody         = m->map(m->handle, LV2_PATCH__body);
        patchSubject      = m->map(m->handle, LV2_PATCH__subject);
        patchProperty     = m->map(m->handle, LV2_PATCH__property);
        patchValue        = m->map(m->handle, LV2_PATCH__value);
        // plugin URIs
        plugBypass        = m->map(m->handle, STRINGIFY(PLUG_URI "_Bypass"));
        plugWaveform      = m->map(m->handle, STRINGIFY(PLUG_URI "_Waveform"));
        plugFrequency     = m->map(m->handle, STRINGIFY(PLUG_URI "_Frequency"));
        plugAmplitude     = m->map(m->handle, STRINGIFY(PLUG_URI "_Amplitude" ));
        plugGain          = m->map(m->handle, STRINGIFY(PLUG_URI "_Gain" ));
        plugPhase         = m->map(m->handle, STRINGIFY(PLUG_URI "_Phase" ));
        // mappings
        plugMap[ModuleType::Oscillator][ParameterType::BYPASS]    = plugBypass ;
        plugMap[ModuleType::Oscillator][ParameterType::WAVEFORM]  = plugWaveform ;
        plugMap[ModuleType::Oscillator][ParameterType::FREQUENCY] = plugFrequency ;
        plugMap[ModuleType::Oscillator][ParameterType::AMPLITUDE] = plugAmplitude ; 
        plugMap[ModuleType::Oscillator][ParameterType::GAIN]      = plugGain ;
        plugMap[ModuleType::Oscillator][ParameterType::PHASE]     = plugPhase ;   
    }

    LV2_URID getPlugURID(ModuleType mtype, ParameterType ptype){
        return plugMap[mtype][ptype] ;
    }
};

// DEFINE PLUGIN STATE PARAMETERS
// define plugin state
struct PluginState {
    LV2_Atom_Bool   bypass ;
    LV2_Atom_Int    waveform ;
    LV2_Atom_Double frequency ;
    LV2_Atom_Double amplitude ;
    LV2_Atom_Double gain ;
    LV2_Atom_Double phase ;

    std::unordered_map<ModuleType, std::unordered_map<ParameterType,void*>> stateMap ;

    PluginState(){
        stateMap[ModuleType::Oscillator][ParameterType::BYPASS]    = &bypass ;
        stateMap[ModuleType::Oscillator][ParameterType::WAVEFORM]  = &waveform ;
        stateMap[ModuleType::Oscillator][ParameterType::FREQUENCY] = &frequency ;
        stateMap[ModuleType::Oscillator][ParameterType::AMPLITUDE] = &amplitude ;
        stateMap[ModuleType::Oscillator][ParameterType::GAIN]      = &gain ;
        stateMap[ModuleType::Oscillator][ParameterType::PHASE]     = &phase ;   
    }

    /**
     * @brief return the atom corresponding to the module/parameter
     * 
     * @tparam ptype 
     */
    template <ParameterType ptype>
    LV2_ATOM_TYPE(ptype)* getAtom(ModuleType mtype){
        return reinterpret_cast<LV2_ATOM_TYPE(ptype)*>(stateMap[mtype][ptype]);
    }
} ;


// DEFINE CONFIGURATION VARIABLES
constexpr std::size_t CONFIG_MAX_BUFFER_SIZE = 2048 ;
constexpr std::size_t CONFIG_NUM_STATE_PARAMETERS = 3 ;
constexpr std::size_t CONFIG_OSCILLATOR_WAVETABLE_SIZE = 1024 ;
constexpr double      CONFIG_DEFAULT_SAMPLE_RATE = 44100 ;
constexpr float       CONFIG_PITCHBEND_MAX_SHIFT = 2 ; // max semitones for midi pitchbend

#endif // __OSCILLATOR_CONFIG_HPP_