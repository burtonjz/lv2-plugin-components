#ifndef __WAVETABLE_HPP_
#define __WAVETABLE_HPP_

#include "plugin.hpp"
#include PLUG_CONFIG
#include "modules/Oscillator/Waveform.hpp"

#include <array>
#include <mutex>

/**
 * class stores all wavetables available to an Oscillator
*/
class Wavetable {
private:
    static std::once_flag initFlag_ ;
    static std::array<std::array<double,CONFIG_OSCILLATOR_WAVETABLE_SIZE>,static_cast<int>(Waveform::N)> wavetable_ ;

public:
    /**
     * @brief generates all wavetables
    */
    static void generate();

    /**
     * @brief return a read-only pointer to the waveform's wavetable
    */
    static const std::array<double,CONFIG_OSCILLATOR_WAVETABLE_SIZE>* getWavetable(Waveform waveform);

private:
    static void generateSineWavetable();
    static void generateSquareWavetable();
    static void generateTriangleWavetable();
    static void generateSawWavetable();
    static void generateNoiseWavetable();

    static double polyBlep(double t, double dt);
};

#endif // __WAVETABLE_HPP_