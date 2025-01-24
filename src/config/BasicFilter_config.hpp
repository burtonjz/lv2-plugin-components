#ifndef __BASIC_FILTER_CONFIG_HPP_
#define __BASIC_FILTER_CONFIG_HPP_


#include <cstddef>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>

#include "plugin.hpp"



// These configuration items are required for any config:
struct PluginState {
    LV2_Atom_Bool bypass ;
    LV2_Atom_Int  bpm ;
    LV2_Atom_Int scaleType ;
    LV2_Atom_Int scaleTonic ;
} ;

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
    LV2_URID plugBpm    ;
    LV2_URID plugScaleType ;
    LV2_URID plugScaleTonic ;


    void initialize(LV2_URID_Map* m){
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
    }
};

constexpr std::size_t CONFIG_NUM_STATE_PARAMETERS = 3 ;
constexpr double      CONFIG_DEFAULT_SAMPLE_RATE = 44100 ;
constexpr float       CONFIG_PITCHBEND_MAX_SHIFT = 2 ; // max semitones for midi pitchbend

#endif 