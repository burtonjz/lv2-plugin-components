#ifndef __KEYBOARD_OBSERVER_HPP_
#define __KEYBOARD_OBSERVER_HPP_

#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <lv2/midi/midi.h>

#include "midi/Note.hpp"

class KeyboardObserver {
public:
    virtual ~KeyboardObserver() = default ;

    virtual void onKeyPressed(const Note* note) ;
    virtual void onKeyReleased(Note note) ;
    virtual void onPitchbend(uint16_t pitchbend );
    virtual void onMidiControlEvent(LV2_Midi_Controller messageType, uint8_t value);
    
};

#endif // __KEYBOARD_OBSERVER_HPP_