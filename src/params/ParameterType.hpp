#ifndef __PARAMETER_TYPE_HPP_
#define __PARAMETER_TYPE_HPP_

#include "modules/Oscillator/Waveform.hpp"

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>

#include <array>
#include <utility>
#include <limits>

/**
 * @brief types of parameters that might exist within any given module
 * 
 * "MC" Parameters are Modulator connection parameters. See ModulationController/ControlPortManager for their uses.
*/
enum class ParameterType {
    BYPASS,
    WAVEFORM,
    FREQUENCY,
    AMPLITUDE,
    GAIN,
    PHASE,
    N_PARAMETERS
};

constexpr int N_PARAMETER_TYPES = static_cast<int>(ParameterType::N_PARAMETERS) ;

/**
 * @brief define value variable type for each ParameterType
*/
template <ParameterType Type> struct ParameterTypeTraits ;
template <> struct ParameterTypeTraits<ParameterType::BYPASS>       {using ValueType = bool   ; using LV2AtomType = LV2_Atom_Bool   ; };
template <> struct ParameterTypeTraits<ParameterType::WAVEFORM>     {using ValueType = int    ; using LV2AtomType = LV2_Atom_Int    ; };
template <> struct ParameterTypeTraits<ParameterType::FREQUENCY>    {using ValueType = double ; using LV2AtomType = LV2_Atom_Double ; };
template <> struct ParameterTypeTraits<ParameterType::AMPLITUDE>    {using ValueType = double ; using LV2AtomType = LV2_Atom_Double ; };
template <> struct ParameterTypeTraits<ParameterType::GAIN>         {using ValueType = double ; using LV2AtomType = LV2_Atom_Double ; };
template <> struct ParameterTypeTraits<ParameterType::PHASE>        {using ValueType = double ; using LV2AtomType = LV2_Atom_Double ; };

/**
 * @brief a std::pair containing the min and max for each parameter type
*/
constexpr std::array<std::pair<float, float>, N_PARAMETER_TYPES> parameterLimits({
    std::make_pair(0.0f, 1.0f),                              // STATUS
    std::make_pair(0.0f,static_cast<float>(Waveform::N)),    // WAVEFORM
    std::make_pair(0.0f, std::numeric_limits<float>::max()), // FREQUENCY
    std::make_pair(0.0f, 1.0f),                              // AMPLITUDE
    std::make_pair(0.0f, 1.0f),                              // GAIN
    std::make_pair(0.0f, 1.0f)                               // PHASE
});

/**
 * @brief a std::array containing the defaults for each parameter type
*/
// constexpr std::array<float, N_PARAMETER_TYPES> parameterDefaults({
//     0.0f,                               // STATUS
//     static_cast<float>(Waveform::SINE), // WAVEFORM
//     440.0f,                             // FREQUENCY
//     1.0f,                               // AMPLITUDE
//     1.0f,                               // GAIN
//     0.0f,                               // PHASE
//     0.0f,                               // PAN
//     0.0f,                               // DETUNE
//     0.01f,                              // ATTACK
//     0.05f,                              // DECAY
//     0.8f,                               // SUSTAIN
//     0.2f,                               // RELEASE
//     0.0f,                               // FILTER_TYPE
//     0.0f,                               // CUTOFF
//     0.5f,                               // Q_FACTOR
//     0.0f,                               // MC_FREQUENCY
//     0.0f,                               // MC_AMPLITUDE
//     0.0f,                               // MC_PHASE
//     0.0f,                               // MC_PAN
// });

#endif // __PARAMETER_TYPE_HPP_