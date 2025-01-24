#ifndef __NOTE_HPP_
#define __NOTE_HPP_

#include <cstdint>
#include <array>

/**
 * @brief storage object for a single midi note
 * 
*/
class Note {
private:
    static std::array<double, 128> frequencies_ ;
    uint8_t midiNote_ ;
    uint8_t midiVelocity_ ;
    bool midiOn_ ;
    double time_ ;

public:
    /**
     * @brief pre-compute data for the note class
     * 
     */
    static void initialize();

    /**
     * @brief Constructor for Note class
     * 
     * @param midiNote the midi note number (0-127)
     * @param midiVelocity the midi velocity (0-127)
     * @param midiOn the key press status
    */
    Note(uint8_t midiNote, uint8_t midiVelocity, bool midiOn);

    /**
     * @brief returns the midi note (0-127)
    */
    uint8_t getMidiNote() const ;

    /**
     * @brief sets the midi note of this data
    */
    void setMidiNote(uint8_t note );

    /**
     * @brief returns the velocity (0-127) of this Note
    */
    uint8_t getMidiVelocity() const ;

    /**
     * @brief sets the velocity of this note. Must be between 0-127.
    */
    void setMidiVelocity(uint8_t velocity);

    /**
     * @brief returns the midi note status
    */
    bool getMidiOn() const ;

    /**
     * @brief sets the midi note status
     * 
    */
    void setIsOn(bool midiOn);

    /**
     * @brief returns the frequency of the specified note
     * 
    */
    static double getFrequency(uint8_t note);

    /**
     * @brief returns the frequency of this Note
    */
    double getFrequency() const ;

    /**
     * @brief gets the time since a MIDI note event
    */
    float getTime() const ;

    /**
     * @brief sets the time since the note was last turned off.
    */
    void tick(double time);

};

#endif // __NOTE_HPP_