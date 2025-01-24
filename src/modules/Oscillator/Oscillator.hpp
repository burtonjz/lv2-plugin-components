#ifndef __MODULE_OSCILLATOR_HPP_
#define __MODULE_OSCILLATOR_HPP_

#include "plugins/PluginResources.hpp"
#include "modules/Module.hpp"

namespace Module {

    class Oscillator : public Module {
    private:
        double phase_ ;
        double increment_ ;
        
    public:
        /**
         * @brief Construct a new Oscillator module
         * 
         * @param plugState pointer to plugin state
         * @param sampleRate plugin sample rate
         */
        Oscillator(PluginResources plugState, double sampleRate);

        /**
         * @brief processes sample and writes to output buffer
         * 
         * @param idx frame to process
         */
        void processSample(uint32_t idx);

        /**
         * @brief increment oscillator for next sample
         */
        void tick() ;
     
    };
}

#endif // __MODULE_OSCILLATOR_HPP_