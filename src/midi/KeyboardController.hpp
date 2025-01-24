#ifndef __KEYBOARD_CONTROLLER_HPP_
#define __KEYBOARD_CONTROLLER_HPP_

#include <lv2/midi/midi.h>
#include <cstdint>
#include <array>
#include <vector>

#include "containers/RTMap.hpp"
#include "midi/KeyboardObserver.hpp"
#include "midi/Note.hpp"

using KeyMap = RTMap<uint8_t, Note, 128> ;

class KeyboardController {
private:
    static std::array<double,16384> pitchbendScaleFactor_ ; // 16384 total number of pitchbend steps (14 bits, -8192 to 8192)

    double sampleRate_ ;

    KeyMap notes_ ;
    uint16_t pitchbend_ ;
    uint8_t sustain_ ;

    std::vector<KeyboardObserver*> observers_ ;

public:
    KeyboardController(double sampleRate);

    // ACTIVATION FUNCTIONS

    /**
     * @brief initialize the keyboard controller. Only run during initialization/activation stages.
     * 
     * Precomputes pitchbend scale factors
    */
    void initialize();

    /**
     * @brief register an observer
     * 
     */
    void registerObserver(KeyboardObserver* observer);

    /**
     * @brief process midi message
     * 
     * @param message_type LV2 Midi message type
     * @param msg The message block of the LV2 Atom
    */
    void processMidi(LV2_Midi_Message_Type message_type, const uint8_t* const msg);

    /**
     * @brief get the pitchbend scale factor (-8192 to 8192)
    */
    float getPitchbend() const ;

    /**
     * @brief get the sustain value (between 0-127)
    */
    uint8_t getSustain() const ;

    void tick(double time) ;

private:
    /**
     * @brief pre-compute pitchbend frequency scale factor array
     * 
     */
    static void computePitchbendScaleFactor();

    /**
     * @brief Set the Sustain value (0-127)
     * 
     */
    void setSustain(uint8_t sustain);

    /**
     * @brief Set the pitchbend value (-8192-8192)
     * 
     */
    void setPitchbend(uint16_t pitchbend);

    // OBSERVER NOTIFICATION FUNCTIONS

    void notifyMidiNoteOn(const Note* note) const ;
    void notifyMidiNoteOff(Note note) const ;
    void notifyMidiPitchbend() const ;
    void notifyMidiControlEvent(LV2_Midi_Controller ctrl, uint8_t value) const ;
};

#endif // __KEYBOARD_CONTROLLER_HPP_