#ifndef __PLUG_OSCILLATOR_HPP_
#define __PLUG_OSCILLATOR_HPP_

#include "plugins/LV2Plugin.hpp"
#include "io/ConnectionManager.hpp"
#include "midi/KeyboardController.hpp"
#include "modules/Oscillator/Oscillator.hpp"

namespace Plugin {

    class Oscillator : public LV2Plugin {
    private:
        ConnectionManager connectionManager_ ;
        KeyboardController keyboardController_ ;
        Module::Oscillator oscillator_ ;

    public:
        // Constructor
        Oscillator(const double sampleRate, const LV2_Feature *const *features);
        
        // API FUNCTIONS
        virtual void connectPort(const uint32_t port, void* data) ;
        virtual void activate() ;
        virtual void run(const uint32_t sampleCount) ;
        virtual void deactivate() ;
    };

}


#endif // __PLUG_OSCILLATOR_HPP_